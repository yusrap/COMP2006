#ifndef LOG_H
#define LOG_H

void logArrival(FILE* testfile, char* buffer);
void logResponse(FILE* testfile, int teller_num, int customer_num);
void logComplete(FILE* testfile, int teller_num, int customer_num, int service_time);
void logTermination(FILE* testfile, int teller_num, int cust_count);

#endif /* LOG_H */