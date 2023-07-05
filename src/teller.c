#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../include/c_queue.h"
#include "../include/shared.h"
#include "../include/log.h"

/* teller function to serve customers */
void *tellerThread(void *arg) {
    TellerThreadData *data = (TellerThreadData *)arg;
    int tellerNum = data->tellerNum;
    SharedData *shared = data->shared;
    int service_time; 

    while (1) {
        pthread_mutex_lock(shared->mutex);  
        if (!isEmpty(shared->queue)) {

            char *customer = dequeue(shared->queue);      

            shared->totalCustomers++;
            data->shared->customersServed[tellerNum]++; 

            logResponse(shared->log_file, tellerNum, shared->totalCustomers);

            int strLength = strlen(customer);

            for (int i = 0; i < strLength; i++) {
                if (customer[i] == 'W') {
                    service_time = shared->WTime;
                } 
                else if (customer[i] == 'D') {
                    service_time = shared->DTime;
                } 
                else if (customer[i] == 'I') {
                    service_time = shared->ITime;
                }
            }
            logComplete(shared->log_file, tellerNum, shared->totalCustomers, service_time);
            pthread_mutex_unlock(shared->mutex);  
            free(customer);
        } 
        else if (shared->totalCustomers == shared->m) {
            pthread_mutex_unlock(shared->mutex);  
            break;  // exit the thread if there are no more incoming customers 
        } 
        else {
            pthread_cond_wait(shared->cond, shared->mutex); 
            pthread_mutex_unlock(shared->mutex);  
        }
    }
    logTermination(shared->log_file,tellerNum,shared->customersServed[tellerNum]);
    pthread_exit(NULL);
}

