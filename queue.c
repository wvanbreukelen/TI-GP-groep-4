/**
 * @file
 * @name Practicum 5_3
 * @author 1696056, Wiebe van Breukelen
 * @brief Huib Aldewereld
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
    pq->count = 0;
}

/**
 * Enqueue
 * @param pq Queue struct pointer
 * @param data Data to enqueue
 */
void enqueue(Queue* pq, ubyte data)
{
    //pq->tail++;
    //count++;

    //assert(pq->tail < QUEUESIZE);
    if (pq->count == QUEUESIZE)
    {
    	//pq->tail = -1;
    	//displayClearTextLine(6);
    	//displayString(6, "Stack overflow on position %d", pq->tail);
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
            //printf("[%d] = %d\n", i, q.a[i]);
        		displayString(i, "[%d] = %d", i, q.a[i]);
        }
    }
}
