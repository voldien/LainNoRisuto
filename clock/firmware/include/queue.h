/**
    Copyright (C) 2017  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _R232_LEDC_QUEUE_H_
#define _R232_LEDC_QUEUE_H_ 1
#include<stdio.h>

/**
 *	Queue data type structure.
 */
struct queue_t{
	uint8_t dequ;			/*	First in position.	*/
	uint8_t enqu;			/*	Last in position.	*/
	const uint8_t size;		/*	Queue size in bytes.	*/
	uint8_t* queue;			/*	Queue byte array.	*/
};

/**
 *	Create queue by initialize data structure.
 *
 *	\queue
 */
extern void init_queue(volatile struct queue_t* queue);

/**
 *	Enqueue.
 */
extern void queue_enqu(volatile struct queue_t* queue, const uint8_t v);

/**
 *	Write null terminated string to queue.
 */
extern void queue_enqustr(volatile struct queue_t* queue, const uint8_t* v);

/**
 *	Dequeue.
 *
 * 	@Return byte in front of the queue.
 */
extern uint8_t queue_dequ(volatile struct queue_t* queue);

/**
 *	Check if queue is empty.
 *
 *	@Return non zero if true.
 */
extern uint8_t queue_empty(volatile const struct queue_t* queue);

/**
 *	Check if queue is full.
 *	@Return
 */
extern uint8_t queue_full(volatile const struct queue_t* queue);

/**
 *	Get size of current queue.
 *
 *	@Return queue->size.
 */
extern const uint8_t queue_size(volatile const struct queue_t* queue);

#endif
