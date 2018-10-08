/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 0            * This file contains the implementations of  *
*             Wyatt Fairbanks               * of the methods for the stack class.        *
*             Dr. John Lusth                *                                            *
*             stack.c                       *                                            *
*             9/11/2018                     *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "da.h"

/*Class definition for STACK. Declares internal data structure, debug flag, and function
  pointers.*/
struct stack {
	DA    *data;
	int    debug;
	void (*display)(void *value, FILE *fp);
	void (*free)(void *value);
};

/*Constructor for STACK. Allocates memory and initializes everything.
 Returns the new STACK.*/
STACK *newSTACK(void) {
	STACK *items = malloc(sizeof(STACK));
	assert(items != 0);
	items->data = newDA();
	items->debug = 0;
	items->display = 0;
	setDAdisplay(items->data, 0);
	items->free = 0;
	setDAfree(items->data, 0);
	return items;
}

/*Method to set the display function for the underlying data type of the STACK.*/
void setSTACKdisplay(STACK * items, void(*display)(void *value, FILE* fp)) {
	items->display = display;
	setDAdisplay(items->data, display);
	return;
}

/*Method to set the free function for the underlying data type of the STACK.*/
void setSTACKfree(STACK * items, void(*free)(void *value)) {
	items->free = free;
	setDAfree(items->data, free);
	return;
}

/*Method to push a new item into the STACK. Uses the underlying data structure's
 insertion method.*/
void push(STACK *items, void *value) {
	insertDAback(items->data, value);
	return;
}

/*Method to pop an item from the STACK. Uses the underlying data structure's
  removal method. Returns the popped item.*/
void *pop(STACK *items) {
	void *popped = removeDAback(items->data);
	assert(sizeDA(items->data) != 0);
	return popped;
}

/*Method to preview the next item to be popped. Uses the underlying data structure's
  retrieval method. Returns the next item.*/
void *peekSTACK(STACK *items) {
	assert(sizeDA(items->data) != 0);
	void *peek = getDA(items->data, sizeDA(items->data) - 1);
	return peek;
}

/*Method to display the contents of the STACK. Uses the debug flag and display
  function pointer to decide display method.*/
void displaySTACK(STACK *items, FILE *fp) {
	if (items->debug > 0) {
		if (items->debug == 1) {
			debugDA(items->data, 0);
			displayDA(items->data, fp);
			return;
		}
		if (items->debug == 2) {
			debugDA(items->data, 1);
			displayDA(items->data, fp);
			return;
		}
	}
	fprintf(fp, "|");
	for (int i = sizeDA(items->data) - 1; i > -1 ; --i)  {
		if (items->display == 0) {
			fprintf(fp, "@%p", getDA(items->data, i));
		}
		else {
			items->display(getDA(items->data, i), fp);
		}
		if (i != 0) {
			fprintf(fp, ",");
		}
	}
	fprintf(fp, "|");
	return;
}

/*Method for setting the STACK debug flag to the specified value. Returns original value.*/
int debugSTACK(STACK *items, int level) {
	int prev = items->debug;
	items->debug = level;
	return prev;
}

/*Method for freeing the memory of the STACK. Calls the free function for the
  underlying data structure.*/
void freeSTACK(STACK *items) {
	freeDA(items->data);
	free(items);
	return;
}

/*Method to get the size of the STACK's underlying data structure. Returns the size.*/
int sizeSTACK(STACK *items) {
	int size = sizeDA(items->data);
	return size;
}