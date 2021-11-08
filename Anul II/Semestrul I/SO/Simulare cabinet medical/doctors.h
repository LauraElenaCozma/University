#ifndef DOCTORS_H_INCLUDED
#define DOCTORS_H_INCLUDED

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

struct node
{
	struct node *next;
	pthread_t thr;
};

void handler_function(int);
int add_node(pthread_t);
void remove_node(pthread_t);
void block_doctor(int *);
void release_doctor(int *);
void add_a_new_patient_thread(pthread_t);
void remove_an_existing_patient(pthread_t);
void * need_a_doctor(void *);
int join_threads(struct node * , struct node *);

#endif // DOCTORS_H_INCLUDED
