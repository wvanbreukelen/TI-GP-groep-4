/**
* @file queue.c
* @author Wiebe van Breukelen
* @date 12-04-2017
* @brief Queue used for Bluetooth command input buffering
*/

#include <queue.h>

/**
 * Init a queue
 * @param pq
 */
void init_queue(Queue* pq)
{
  pq->head = 0;
  pq->tail = 0;

  // Amount of items in queue
  pq->count = 0;
}

/**
 * Enqueue
 * @param pq Queue struct pointer
 * @param data Data to enqueue
 */
void enqueue(Queue* pq, ubyte data)
{
    if (pq->count == QUEUESIZE)
    {
    	// Queue overflow
    	return;
    }

    pq->a[pq->tail] = data;
    pq->tail--;

    if (pq->tail == -1)
    {
    	pq->tail = QUEUESIZE - 1;
    }

    pq->count++;
}

/**
 * Dequeue
 * @param pq Queue struct pointer
 * @param data Data to dequeue
 */
ubyte dequeue(Queue* pq)
{
	if (pq->count == 0)
	{
		// Nothing in queue, return zero
		return 0;
	}

	ubyte data = pq->a[pq->head];
  pq->head--;

  if (pq->head == -1)
  {
  	pq->head = QUEUESIZE - 1;
  }

  pq->count--;

 	return data;
}

/**
 * Show queue
 * @param q
 */
void show(Queue q)
{
  if (q.tail > -1)
  {
    for (int i = 0; i < QUEUESIZE; i++)
    {
    		displayString(i, "[%d] = %d", i, q.a[i]);
    }
  }
}
