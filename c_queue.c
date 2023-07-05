#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct to hold queue */
struct Queue {
    int front, rear, size;
    unsigned capacity;
    char** array;
};

/* create queue of given capacity and initialise it to 0 */
struct Queue* createQueue(unsigned capacity){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    queue->rear = capacity - 1;
    queue->array = (char**)malloc(queue->capacity * sizeof(char*)); 
    for (int i = 0; i < queue->capacity; i++) {
        queue->array[i] = (char*)malloc(3 * sizeof(char));
        strcpy(queue->array[i], "0 ");
    }
    return queue;
}

/* check if queue is empty */
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

/* check if queue is full */
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

/* Add element to end of queue */
void enqueue(struct Queue* queue, char* item)
{
	if (isFull(queue))
		return;

	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = malloc((strlen(item) + 1) * sizeof(char)); 
	strcpy(queue->array[queue->rear], item); 
	queue->size = queue->size + 1;
}

/* Remove an element from the front of the queue*/
char* dequeue(struct Queue* queue)
{
	if (isEmpty(queue)){
		return NULL;
	}

	char* item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;

	return item;
}

/* Get value at the front of queue without removing it */
char* front(struct Queue* queue)
{
	if (isEmpty(queue))
		return "Empty queue";
	return queue->array[queue->front];
}

/* Get value at the end of queue without removing it */
char* rear(struct Queue* queue)
{
	if (isEmpty(queue))
		return "Empty queue";
	return queue->array[queue->rear];
}

/* Destroy resources taken up by queue */
void destroyQueue(struct Queue* queue) {
    for (int i = 0; i < queue->capacity; i++) {
        free(queue->array[i]); 
    }
    free(queue->array); 
    free(queue);
}

