#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h> 
#include "generate_c_file.h"
#include "c_queue.h"
#include "customer.h"
#include "teller.h"
#include "shared.h"

int main(int argc, char *argv[]) {

    /* Declare threads, mutex locks and wait/signal condition */
    pthread_t customer_thread;
    pthread_t teller_threads[4];  

    pthread_mutex_t mutex; 
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_t cond; 
    pthread_cond_init(&cond, NULL);

    /* Create structures to hold shared data and teller thread data */
    SharedData data;
    TellerThreadData threadData[4];

    if (argc == 6) {

        /* assign shared data values */
        data.m = atoi(argv[1]);
        data.ATime = atoi(argv[2]);
        data.WTime = atoi(argv[3]);
        data.DTime = atoi(argv[4]);
        data.ITime = atoi(argv[5]);
        data.mutex = &mutex;
        data.cond = &cond;
        data.queue = createQueue(data.m);
        data.totalCustomers = 0;
        data.log_file = fopen("r_log.txt", "w");

        /* check if all arguments be positive integers */
        if (data.m>0 && data.ATime>0 && data.WTime>0 && data.DTime>0 && data.ITime>0){  
            
            /* generate c_file containing 100 customers */
            generate_c_file();  

            /* create customer thread */
            if (pthread_create(&customer_thread, NULL, customerThread, (void*)&data)){
                printf("Failed to create customer thread\n");
                return 1;
            }
            
            /* wait for customer thread to finish */
            if (pthread_join(customer_thread, NULL)){
                printf("Failed to join thread\n");
                return 1;
            }

            /* initialise customer count for each teller to 0 */
            for (int i = 0; i < 4; i++) {
                data.customersServed[i] = 0;
            }

            /* create 4 teller threads */
            for (int i=0;i<4;i++){
                threadData[i].tellerNum = i+1;
                threadData[i].shared = &data;
                if (pthread_create(&teller_threads[i], NULL, tellerThread, (void*)&threadData[i])){
                    printf("Failed to create teller thread %d", i);
                    return 1;
                }
            }   

            /* wait for teller threads to finish */
            for (int i = 0; i < 4; i++) {
                if (pthread_join(teller_threads[i], NULL)) {
                    printf("Error joining teller thread\n");
                    return 1;
                }
            }  

            /* log teller statistics to r_log file */
            fprintf(data.log_file, "\nTeller Statistic\n");
            for (int i = 0; i < 4; i++) {
                fprintf(data.log_file, "Teller-%d serves %d customers.\n", i + 1, data.customersServed[i+1]);
            }
            fprintf(data.log_file, "\nTotal number of customers: %d customers.", data.totalCustomers);
            fflush(data.log_file);

            /* clean up resources */
            destroyQueue(data.queue);
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);
            fclose(data.log_file);
        }
        else {
            printf("Error: arguments must be positive integers\n");  
        }
        }
    else {
        printf("Error: expected 6 arguments, got %d\n", argc - 1); 
    }
    return 0;
}
