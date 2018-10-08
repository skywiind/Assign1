/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 0            * This file contains the implementations of  *
*             Wyatt Fairbanks               * the methods for the queue class.           *
*             Dr. John Lusth                *                                            *
*             queue.c                       *                                            *
*             9/12/2018                     *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "cda.h"

/*Class definition for QUEUE. Declares internal data structure, debug flag, and function
  pointers.*/
struct queue {
	CDA   *data;
	int    debug;
	void (*display)(void *value, FILE *fp);
	void (*free)(void *value);
};

/*Constructor for QUEUE. Allocates memory and initializes everything.
  Returns the new QUEUE.*/
QUEUE *newQUEUE(void) {
	QUEUE *items = malloc(sizeof(QUEUE));
	assert(items != 0);
	items->data = newCDA();
	items->debug = 0;
	items->display = 0;
	setCDAdisplay(items->data, 0);
	items->free = 0;
	setCDAfree(items->data, 0);
	return items;
}

/*Method to set the display function for the underlying data type of the QUEUE.*/
void setQUEUEdisplay(QUEUE *items, void(*display)(void *value, FILE *fp)) {
	items->display = display;
	setCDAdisplay(items->data, display);
	return;
}

/*Method to set the free function for the underlying data type of the QUEUE.*/
void setQUEUEfree(QUEUE * items, void(*free)(void *value)) {
	items->free = free;
	setCDAfree(items->data, free);
	return;
}

/*Method to queue a new item into the QUEUE. Uses the underlying data structure's
 insertion method.*/
void enqueue(QUEUE *items, void *value) {
	insertCDAback(items->data, value);
	return;
}

/*Method to dequeue an item from the QUEUE. Uses the underlying data structure's
  removal method. Returns the dequeued item.*/
void *dequeue(QUEUE *items) {
	assert(sizeCDA(items->data) != 0);
	return removeCDAfront(items->data);
}

/*Method to preview the next item to be dequeued. Uses the underlying data structure's
  retrieval method. Returns the next item.*/
void *peekQUEUE(QUEUE *items) {
	assert(sizeCDA(items->data) != 0);
	return getCDA(items->data, 0);
}

/*Method to display the contents of the QUEUE. Uses the debug flag and display
  function pointer to decide display method.*/
void displayQUEUE(QUEUE *items, FILE *fp) {
	if (items->debug > 0) {
		if (items->debug == 1) {
			displayCDA(items->data, fp);
			return;
		}
		if (items->debug == 2) {
			debugCDA(items->data, 1);
			displayCDA(items->data, fp);
			return;
		}
	}

	fprintf(fp, "<");
	for (int i = 0; i < sizeCDA(items->data); i++) {
		if (items->display == 0) {
			fprintf(fp, "@%p", getCDA(items->data, i));
		}
		else {
			items->display(getCDA(items->data, i), fp);
		}
		if (i != (sizeCDA(items->data) - 1)) {
			fprintf(fp, ",");
		}
	}
	fprintf(fp, ">");
	return;
}

/*Method for setting the QUEUE debug flag to the specified value. Returns original value.*/
int debugQUEUE(QUEUE *items, int level) {
	int prev = items->debug;
	items->debug = level;
	return prev;
}

/*Method for freeing the memory of the QUEUE. Calls the free function for the
  underlying data structure.*/
void freeQUEUE(QUEUE *items) {
	freeCDA(items->data);
	free(items);
	return;
}

/*Method to get the size of the QUEUE's underlying data structure. Returns the size.*/
int sizeQUEUE(QUEUE *items) {
	int size = sizeCDA(items->data);
	return size;
}