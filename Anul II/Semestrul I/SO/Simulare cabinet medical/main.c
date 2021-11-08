#include "doctors.h"
int noOfDoctors;
_Bool *doctorTaken;
_Bool closedCabinet;
pthread_mutex_t mtx;
sem_t sem;
int counter; //current number of nodes in the list
struct node *head , *tail;

int main(int argc , char ** argv)
{
    srand(time(NULL));
    signal(SIGINT , handler_function);

    if(argc < 2)
    {
        fprintf(stderr , "Invalid number of arguments\n");
        return -1;
    }

    noOfDoctors = atoi(argv[1]);
    doctorTaken = (_Bool *)malloc(noOfDoctors * sizeof(_Bool));
	if(pthread_mutex_init(&mtx , NULL))
    {
        perror(NULL);
        return errno;
    }
    if(sem_init(&sem , 0 , noOfDoctors))
    {
        perror(NULL);
        return errno;
    }

    head = NULL;
	tail = NULL;
	int patientId = 1;

	while(1)
    {
        if(closedCabinet == 1){ break;}
        if(counter < maxNumberOfPatients)
        {
            unsigned long long timeWaitingPatient = rand() % timePatient + 1; //a patient will be generated in 1, 2 or 3 seconds
            sleep(timeWaitingPatient);
            printf("Patient no. %d\n" , patientId);
            int *index;
            index = (int *)malloc(sizeof(int));

            if(index == NULL)
            {
                fprintf(stderr , "Lack of memory");
                return -1;
            }
            //create a patient thread
            //the parameter of need_a_doctor is index
            (*index) = patientId;
            pthread_t t;
            if(pthread_create(&t , NULL , need_a_doctor , index))
            {
                perror(NULL);
                return errno;
            }

           patientId++;

        }

	}
    join_threads(head , tail);
    pthread_mutex_destroy(&mtx);
    sem_destroy(&sem);
    free(doctorTaken);
    return 0;
}
