/**
 * @file
 * @name Practicum 5_3
 * @author 1696056, Wiebe van Breukelen
 * @brief Huib Aldewereld
 */

#ifndef INC_5_3_QUEUE_H
#define INC_5_3_QUEUE_H

#define QUEUESIZE 10

typedef struct
{
    ubyte a[QUEUESIZE];
    int head;
    int tail;
    int count;
} Queue;

void init_queue(Queue* pq);
void enqueue(Queue* pq, ubyte data);
ubyte dequeue(Queue* pq);
void show(Queue q);

#endif //INC_5_3_QUEUE_H
