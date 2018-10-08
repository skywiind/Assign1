/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 0            * This file contains the implementations of  *
*             Wyatt Fairbanks               * the methods for the dynamic array class.   *
*             Dr. John Lusth                *                                            *
*             da.c                          *                                            *
*             8/21/2018                     *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

/*Class definition for DA. Declares all internal data structures, counters, and
  function pointers.*/
struct da {
	void **arr;
	int    size;
	int    cap;
	int    debug;
	void (*display)(void *value, FILE *fp);
	void (*free)(void *value);
};

/*Constructor for DA. Allocates memory and initializes everything. Returns the new DA.*/
DA   *newDA(void) {
	DA *items      = malloc(sizeof(DA));
	assert(items != 0);
	items->arr     = malloc(sizeof(void *));
	items->size    = 0;
	items->cap     = 1;
	items->debug   = 0;
	items->display = 0;
	items->free    = 0;
	return items;
}

/*Method to set the display function for the underlying data type of the DA.*/
void  setDAdisplay(DA *items, void(*display)(void *value , FILE *fp)) {
	items->display = display;
	return;
}

/*Method to set the free function for the underlying data type of the DA.*/
void  setDAfree(DA *items, void(*free)(void *value)) {
	items->free = free;
	return;
}

/*Method to insert new items into DA. Manages memory using a temp array,
  inserts shifting right.*/
void insertDA(DA *items, int index, void *value) {
	if (items->size == items->cap) {
		items->cap *= 2;
		void **temp = items->arr;
		items->arr = malloc((sizeof(void *)) * items->cap);
		assert(items->arr != 0);
		for (int i = 0; i < items->size; i++) {
			items->arr[i] = temp[i];
		}
		free(temp);
	}
	for (int i = items->size - 1; i >= index; i--) {
		items->arr[i + 1] = items->arr[i];
	}
	items->size++;
	items->arr[index] = value;
	return;
}

/*Method to remove items from the DA. Manages memory using a temp array,
  removes shifting left. Returns the removed item.*/
void *removeDA(DA *items, int index) {
	assert(items->size != 0);
	if ((items->size * 4) < items->cap) {
		items->cap /= 2;
		void **temp = items->arr;
		items->arr = malloc((sizeof(void *) * items->cap));
		for (int i = 0; i < items->size; i++) {
			items->arr[i] = temp[i];
		}
		free(temp);
	}
	void *removed = items->arr[index];
	for (int i = index; i < (items->size - 1); i++) {
		items->arr[i] = items->arr[i + 1];
	}
	items->size--;
	if (items->size == 0) {
		items->cap = 1;
	}
	return removed;
}

/*Method to combine two DAs. Uses a temp array and repeated insertion to add the donor
  array's contents to the recipient.*/
void  unionDA(DA *recipient, DA *donor) {
	void **temp = donor->arr;
	for (int i = 0; i < (donor->size); i++) {
		insertDA(recipient, recipient->size, temp[i]);
	}
	donor->size = 0;
	donor->cap  = 1;
	donor->arr  = malloc(sizeof(void *));
	free(temp);
	return;
}

/*Method for retrieving the value stored in the DA at the target index.
  Returns the targeted value.*/
void *getDA(DA *items, int index) {
	assert(index >= 0 && index < items->size);
	return items->arr[index];
}

/*Method for replacing a value in the DA at the targeted index. If target index 
  is empty, value is inserted. If not, original value is replaced and returned.*/
void *setDA(DA *items, int index, void *value) {
	assert(index >= 0 && index <= items->size);
	if (index == items->size) {
		insertDA(items, index, value);
		return 0;
	}
	void *temp = items->arr[index];
	items->arr[index] = value;
	return temp;
}

/*Method for retrieving the size of the DA. Returns the size.*/
int   sizeDA(DA *items) {
	return items->size;
}

/*Method for displaying the contents of the DA. Uses the debug flag and display
  function pointer to decide display method.*/
void  displayDA(DA *items, FILE *fp) {
	fprintf(fp, "[");
	if (items->size == 0 && items->debug > 0) {
		fprintf(fp, "[%d]", ((items->cap) - (items->size)));
	}
	for (int i = 0; i < items->size; i++) {
		if (items->display == 0) {
			fprintf(fp, "@%p", items->arr[i]);
		}
		else {
			items->display(items->arr[i], fp);
		}
		if (items->debug > 0 && i == (items ->size) - 1) {
			fprintf(fp, ",[%d]", ((items->cap) - (items->size)));
		}
		if (i != (items->size) - 1) {
			fprintf(fp, ",");
		}
	}
	fprintf(fp, "]");
	return;
}

/*Method for setting the DA debug flag to the specified value. Returns original value.*/
int   debugDA(DA *items, int level) {
	int prev = items->debug;
	items->debug = level;
	return prev;
}

/*Method for freeing the memory of the DA. Calls the set free function for each
  item in the array. If no function is set, it simply frees the whole array.*/
void  freeDA(DA *items) {
	if (items->free != 0) {
		for (int i = 0; i < items->size; i++) {
			items->free(items->arr[i]);
		}
	}
	free(items->arr);
	free(items);
	return;
}