#include"queue.h"
#include<avr/pgmspace.h>
#include<stdio.h>
#include<stdlib.h>

void init_queue(volatile struct queue_t* queue){

	queue->queue = malloc(queue->size);
	queue->dequ = 0;
	queue->enqu = 0;
}

void queue_enqu(volatile struct queue_t* queue, const uint8_t v){
	queue->queue[queue->enqu] = v;
	queue->enqu++;
	queue->enqu %= queue->size;
}

void queue_enqustr(volatile struct queue_t* queue, const uint8_t* v){
	while(*v != '\0'){
		queue_enqu(queue, *v);
		v++;
	}
}

uint8_t queue_dequ(volatile struct queue_t* queue){
	uint8_t v = queue->queue[queue->dequ];
	queue->dequ--;
	queue->dequ %= queue->size;
	return v;
}

uint8_t queue_empty(volatile const struct queue_t* queue){
	return queue->dequ == queue->enqu;
}

uint8_t queue_full(volatile const struct queue_t* queue){
	return ( (queue->enqu + 1) % queue->size) == queue->dequ;
}

const uint8_t queue_size(volatile const struct queue_t* queue){
	return queue->enqu - queue->dequ;	/*	TODO resolve.	*/
}
