#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "c_queue.h"
#include "shared.h"
#include "log.h"

/* Adds customers to queue */
void *customerThread(void *arg) {
    SharedData *data = (SharedData *)arg;

    char buffer[10];
    int line_num = 1;

    time_t rawtime;

    FILE* c_file = fopen("c_file.txt", "r");

    if (data->log_file == NULL || c_file == NULL) {
        printf("Failed to open file\n");
        return NULL;
    }    

    while (line_num <= data->m) {
        if (fgets(buffer, sizeof(buffer), c_file) != NULL) {

            pthread_mutex_lock(data->mutex);
            enqueue(data->queue, buffer); 

            time(&rawtime);
            logArrival(data->log_file,buffer);

            pthread_mutex_unlock(data->mutex);
            pthread_cond_signal(data->cond);

            line_num++;
        } 
        else {
            printf("End of file reached before maximum capacity was reached\n");
            break;
        }
        
        sleep(data->ATime);
    }

    fclose(c_file);
    pthread_exit(NULL);
}


