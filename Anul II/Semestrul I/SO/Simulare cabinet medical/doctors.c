#include "doctors.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define MAX_CONSULTATION_TIME 15
#define maxNumberOfPatients 10
#define timePatient 2
int noOfDoctors;
_Bool *doctorTaken;
_Bool closedCabinet;
pthread_mutex_t mtx;
sem_t sem;
int counter; //current number of nodes in the list
struct node *head , *tail;
void handler_function(int signum)
{
    //when pressing ctrl + c closedCabinet = 1
	printf("\nCLOSED CABINET\n");
	closedCabinet = 1; //used later
}

int add_node(pthread_t thr)
{
    //add the thread thr in the list of threads
	struct node * newNode = (struct node *)malloc(sizeof(*newNode));
	if(newNode == NULL)
    {
        printf("Allocation failure when creating a new node\n");
        closedCabinet = 1;
        perror(NULL);
        return errno;
    }
	newNode->next = NULL;
	newNode->thr = thr;
	if(head == NULL)    //if the list is empty
	{
        head = newNode;
        tail = newNode;
    }
	else                //if the list isn't empty
    {                   //add the node at the end of the list
        tail->next = newNode;
        tail = newNode;
    }


}

void remove_node(pthread_t thr)
{
    //remove the node of the thr thread
	struct node * nod;
	nod = head;
    //go through the list and search for that node
	while(nod -> thr != thr)
    {
        nod = nod -> next;
    }

	if(head == nod)
	{
	    //remove the first node
		if(head->next == NULL)
		{
		    //if the list contains only one node
			free(head);
			head = NULL;
			tail = NULL;
		}
		else
		{
			struct node * n = head;
			head = head -> next;
			free(n);
		}
	}
	else
	{   //find the previous node of the node we want to remove
		struct node *prev = head;
		while(prev->next != nod)
		{
			prev = prev->next;
		}
		struct node *n = nod;
		prev->next = nod->next;
		if(prev->next == NULL)
			tail = prev;    //update the thread
		free(n);
	}
}


void block_doctor(int *doctor)
{
    //search for the first free doctor
    pthread_mutex_lock(&mtx);
    for(int i = 0 ; i < noOfDoctors ; i++)
	if(!doctorTaken[i])
	{
		doctorTaken[i] = 1;
		(*doctor) = i;
		break;
	}
    printf("DOCTOR %d HAS A CONSULTATION\n" , (*doctor) + 1);
    pthread_mutex_unlock(&mtx);
}

void release_doctor(int *doctor)
{
    //update the doctors. Set doctor as free
    pthread_mutex_lock(&mtx);
    doctorTaken[(*doctor)] = 0;
    printf("DOCTOR %d ENDED A CONSULTATION\n" , (*doctor) + 1);
    pthread_mutex_unlock(&mtx);
}

void add_a_new_patient_thread(pthread_t thr)
{
    //add a new node into the list
	pthread_mutex_lock(&mtx);
	add_node(thr);
	counter ++;//new node was built
	pthread_mutex_unlock(&mtx);
}

void remove_an_existing_patient(pthread_t thr)
{
    //remove the thread thr from the list
	pthread_mutex_lock(&mtx);
	remove_node(thr);
	counter --; //node deleted
	pthread_mutex_unlock(&mtx);
}
void * need_a_doctor(void *noP)
{
    //build a thread
    if(closedCabinet == 0)
    {
        int arrivalTime = time(NULL);
        pthread_t myPid = pthread_self();
        add_a_new_patient_thread(myPid);

        if(sem_wait(&sem))
        {
            perror(NULL);
            return errno;
        }

        int * noOfPatient = (int *)noP;

        int *indexDoctor;
        indexDoctor = (int *)malloc(sizeof(int));
        block_doctor(indexDoctor);          //search the first free doctor

        time_t currentTime = time(NULL);
        unsigned long long periodBlockDoctor = rand() % MAX_CONSULTATION_TIME + 1; //between 1 and MAX_CONSULTATION_TIME - 1
        printf("Under consultation doctor %d with patient %d\n" , (*indexDoctor) + 1 , *noOfPatient);
        sleep(periodBlockDoctor);

        release_doctor(indexDoctor);         //update doctorTaken[]
        printf("Patient %d with doctor %d waited for %ld seconds and the consultation took %lld seconds\n" , (*noOfPatient) , (*indexDoctor) + 1 , currentTime - arrivalTime , periodBlockDoctor);
        if(sem_post(&sem))
        {
            perror(NULL);
            return errno;
        }
        remove_an_existing_patient(myPid);  //delete the thread from the list

    }

    return NULL;
}
int join_threads(struct node * head , struct node *tail)
{
    //join the threads
	struct node * auxHead;
	struct node * auxTail;
	auxHead = NULL;
	auxTail = NULL;
    //make a copy of the list
	for(struct node * nod = head ; nod != NULL ; nod = nod->next)
	{
		struct node * newNode;
		newNode = (struct node *)malloc(sizeof(*newNode));
		newNode -> next = NULL;
		newNode -> thr = nod -> thr;
		if(auxHead == NULL)
		{
		    //if the list is empty
			auxHead = newNode;
			auxTail = auxHead;
		}
		else
		{
			auxTail -> next = newNode;
			auxTail = newNode;
		}
	}

	for(struct node * nod = auxHead ; nod != NULL ; nod = nod -> next)
	{
	    //join the threads from the list
		if(pthread_join(nod -> thr , NULL))
		{
			perror(NULL);
			return errno;
		}
	}
    //clear the list
	while(head != NULL)
    {
        struct node * nod = head;
        head = head -> next;
        free(nod);
    }
}

