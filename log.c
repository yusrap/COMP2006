#include <time.h>
#include <stdio.h>
#include <unistd.h>

/* logs arrival of customer into queue in the r_log file */
void logArrival(FILE* testfile, char* buffer){
    struct tm *arrival_time;
    time_t rawtime;
    time(&rawtime);
    arrival_time = localtime(&rawtime);

    fprintf(testfile, "\n-----------------------------------------------------------------------");
    fprintf(testfile, "\n%sArrival Time: %02d:%02d:%02d\n", buffer, arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec);
    fprintf(testfile, "-----------------------------------------------------------------------\n");
    fflush(testfile);
}

/* logs when customer is taken up by teller in the r_log file */
void logResponse(FILE* testfile, int teller_num, int customer_num, int service_time){
    struct tm *arrival_time;
    struct tm *response_time;
    time_t rawtime;

    time(&rawtime);
    arrival_time = localtime(&rawtime);
    fprintf(testfile,"\nTeller: %d\n", teller_num);
    fprintf(testfile,"Customer: %d\n", customer_num);
    fprintf(testfile,"Arrival Time: %02d:%02d:%02d\n", arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec);

    time(&rawtime);
    response_time = localtime(&rawtime);
    fprintf(testfile,"Response Time: %02d:%02d:%02d\n", response_time->tm_hour, response_time->tm_min, response_time->tm_sec);
    fflush(testfile);
}

/* logs when customer is completely served in the r_log file */
void logComplete(FILE* testfile, int teller_num, int customer_num, int Stime){
    struct tm *arrival_time;
    struct tm *completion_time;
    time_t rawtime;
    
    time(&rawtime);
    arrival_time = localtime(&rawtime);
    
    fprintf(testfile, "\nTeller: %d\n", teller_num);
    fprintf(testfile, "Customer: %d\n", customer_num);
    fprintf(testfile,"Arrival Time: %02d:%02d:%02d\n", arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec);

    sleep(Stime);

    time(&rawtime);
    completion_time = localtime(&rawtime);
    fprintf(testfile, "Completion Time: %02d:%02d:%02d\n", completion_time->tm_hour, completion_time->tm_min, completion_time->tm_sec);
    fflush(testfile);
}

/* logs when all tellers terminate their operations in the r_log file */
void logTermination(FILE* testfile, int teller_num, int cust_count){
    struct tm *termination_time;
    time_t rawtime;

    time(&rawtime);
    termination_time = localtime(&rawtime);

    fprintf(testfile, "\nTermination: Teller-%d\n", teller_num);
    fprintf(testfile, "#served customers: %d\n", cust_count);
    fprintf(testfile, "Termination Time: %02d:%02d:%02d\n", termination_time->tm_hour, termination_time->tm_min, termination_time->tm_sec);
    
    fflush(testfile);
}
