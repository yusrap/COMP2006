#ifndef QUEUE_H
#define QUEUE_H

struct Queue* createQueue(unsigned capacity);
int isEmpty(struct Queue* queue);
int isFull(struct Queue* queue);
void enqueue(struct Queue* queue, char* item);
char* dequeue(struct Queue* queue);
char* front(struct Queue* queue);
char* rear(struct Queue* queue);
void destroyQueue(struct Queue* queue);

#endif /* QUEUE_H */


