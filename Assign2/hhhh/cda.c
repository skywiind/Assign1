/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 0            * This file contains the implementations of  *
*             Wyatt Fairbanks               * the methods for the circular dynamic       *
*             Dr. John Lusth                * array class.                               *
*             cda.c                         *                                            *
*             8/21/2018                     *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cda.h"

/*Class definition for CDA. Declares all internal data structures, counters, and
  function pointers.*/
struct cda {
	void **arr;
	int    size;
	int    cap;
	int    debug;
	int    start;
	void(*display)(void *value, FILE *fp);
	void(*free)(void *value);
};

/*Constructor for CDA. Allocates memory and initializes everything. Returns the new CDA.*/
CDA *newCDA(void) {
	CDA *items = malloc(sizeof(CDA));
	assert(items != 0);
	items->arr = malloc(sizeof(void *));
	items->size = 0;
	items->cap = 1;
	items->debug = 0;
	items->start = 0;
	items->display = 0;
	items->free = 0;
	return items;
}

/*Method to set the siplay function for the underlying data type of the CDA.*/
void setCDAdisplay(CDA *items, void(*display)(void *value, FILE *fp)) {
	items->display = display;
	return;
}

/*Method to set the free function for the underlying data type of the CDA.*/
void setCDAfree(CDA *items, void(*free)(void *value)) {
	items->free = free;
	return;
}

/*Internal utility function. Changes a user-scope index to the internal scope.*/
int indexCDA(CDA *items, int index) {
	return ((items->start + index) + items->cap) % items->cap;
}

/*Method to manage memory, expand or contracting as necessary.*/
void memCDA(CDA *items) {
	if (items->size == items->cap) {
		void **temp = items->arr;
		items->arr = malloc((sizeof(void *)) * (items->cap * 2));
		for (int i = 0; i < items->size; i++) {
			items->arr[i] = temp[indexCDA(items, i)];
		}
		items->start = 0;
		items->cap *= 2;
		free(temp);
		return;
	}
	if ((items->size * 4) < items->cap) {
		void **temp = items->arr;
		items->arr = malloc((sizeof(void*)) * (items->cap / 2));
		for (int i = 0; i < items->size; i++) {
			items->arr[i] = temp[indexCDA(items, i)];
		}
		items->start = 0;
		items->cap /= 2;
		free(temp);
		return;
	}
	return;
}

/*Method to insert new items into CDA. Manages memory using a temp array,
  inserts, shifting based on efficiency.*/
void insertCDA(CDA *items, int index, void *value) {
	//Manage memory
	if (items->size == items->cap) {
		memCDA(items);
	}

	//Insert at front
	if (index == 0) {
		//Insert first item
		if (items->size == 0) {
			items->arr[0] = value;
			items->size++;
			return;
		}
		items->arr[indexCDA(items, -1)] = value;
		items->start = indexCDA(items, -1);
		items->size++;
		return;
	}

	//Insert at back
	else if (index == items->size) {
		items->arr[indexCDA(items, items->size)] = value;
		items->size++;
		return;
	}
	else {
		//Insert right of center
		if (index > items->size / 2) {
			for (int i = items->size; i > index; i--) {
				items->arr[indexCDA(items, i)] = items->arr[indexCDA(items, i - 1)];
			}
			items->arr[indexCDA(items, index)] = value;
		}
		//Insert left of center
		else if (index <= items->size / 2) {
			for (int i = -1; i < index - 1; i++) {
				items->arr[indexCDA(items, i)] = items->arr[indexCDA(items, i + 1)];
			}
			items->arr[indexCDA(items, index - 1)] = value;
			items->start = (indexCDA(items, -1));
		}
		items->size++;
	}
	return;
}

/*Method to remove items from the CDA. Manages memory using a temp array,
  removes, shifting based on efficiency. Returns the removed item.*/
void *removeCDA(CDA *items, int index) {

	assert(index >= 0);
	if (index > items->size) {
		return NULL;
	}
	void *removed = items->arr[indexCDA(items, index)];

	//Remove at front
	if (index == 0) {
		items->start = indexCDA(items, 1);
	}
	
	else if (index > 0 && index < (items->size - 1)) {
		//Remove right of center
		if (index > items->size / 2) {
			for (int i = index; i < items->size - 1; i++) { 
				items->arr[indexCDA(items, i)] = items->arr[indexCDA(items, i + 1)];
			}
		}
		//Remove left of center
		else if (index <= items->size / 2) {
			for (int i = index; i > 0; i--) { 
				items->arr[indexCDA(items, i)] = items->arr[indexCDA(items, i - 1)];
			}
			items->start = indexCDA(items, 1);
		}
	}
	items->size--;
	
	//Manage memory
	if (items->size == 0) {
		items->arr = realloc(items->arr, sizeof(void *));
		items->cap = 1;
		items->start = 0;
	}
	else if ((items->size * 4) < items->cap) {
		memCDA(items);
	}
	return removed;
}

/*Method for joing two CDAs. Uses a temp array and repeated insertion to 
  add donor array's contents to the recipient.*/
void unionCDA(CDA *recipient, CDA *donor) {
	void **temp = donor->arr;
	for (int i = 0; i < donor->size; i++) {
		insertCDAback(recipient, donor->arr[indexCDA(donor, i)]);
	}
	donor->size = 0;
	donor->cap = 1;
	donor->arr = malloc(sizeof(void *));
	free(temp);
	return;
}

/*Method for retriving value stored in CDA at target index.
  Returns the targeted value.*/
void *getCDA(CDA *items, int index) {
	assert(index >= 0 && index < items->size);
	return items->arr[indexCDA(items, index)];
}


/*Method for replacing a value in the CDA at the target index. If empty,
  value is inserted. If not, original value is replaced and returned.*/
void *setCDA(CDA *items, int index, void *value) {
	assert(index >= -1 && index <= items->size);
	if (index == -1) {
		insertCDAfront(items, value);
		return 0;
	}
	if (index == items->size) {
		insertCDAback(items, value);
		return 0;
	}
	void *temp = items->arr[indexCDA(items, index)];
	items->arr[indexCDA(items, index)] = value;
	return temp;
}

/*Method for retrieving the size of the CDA. Returns the size.*/
int sizeCDA(CDA *items) {
	return items->size;
}

/*Method for displaying the contents of the CDA. Uses the debug flag and
  display function pointer to decide display method.*/
void displayCDA(CDA *items, FILE *fp) {
	fprintf(fp, "(");
	if (items->size == 0 && items->debug > 0) {
		fprintf(fp, "(%d)", ((items->cap) - (items->size)));
	}
	for (int i = 0; i < items->size; i++) {
		if (items->display == 0) {
			fprintf(fp, "@%p", items->arr[indexCDA(items, i)]);
		}
		else {
			items->display(items->arr[indexCDA(items, i)], fp);
		}
		if (items->debug > 0 && i == (items->size - 1)) {
			fprintf(fp, ",(%d)", ((items->cap) - (items->size)));
		}
		if (i != (items->size) - 1) {
			fprintf(fp, ",");
		}
	}
	fprintf(fp, ")");
	return;
}

/*Method for setting the CDA debug flag to the specified value. Returns original value.*/
int debugCDA(CDA *items, int level) {
	int prev = items->debug;
	items->debug = level;
	return prev;
}

/*Method for freeing the memory of the CDA. Calls the set free function for each
  item in the array. If no functions if set, it simply frees the whole array.*/
void freeCDA(CDA *items) {
	if (items->free != 0) {
		for (int i = 0; i < items->size; i++) {
			items->free(items->arr[indexCDA(items, i)]);
		}
	}
	free(items->arr);
	free(items);
	return;
}