#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

/* Define structure*/
typedef struct {
    int m, ATime, WTime, DTime, ITime;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
    struct Queue* queue;
    int totalCustomers;
    int customersServed[4];
    FILE* log_file; 
} SharedData;

typedef struct{
    int tellerNum;
    SharedData* shared;
} TellerThreadData;

#endif /* SHARED_H */

