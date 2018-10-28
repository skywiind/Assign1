#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"

int main() {

	printf("Constructing Tree...\n");

	BST *tree = newBST(compareINTEGER);
	setBSTdisplay(tree, displayINTEGER);
	setBSTfree(freeINTEGER);

	printf("Generating values...\n");

	int vals[5];

	printf("     Values generated: ");
	for (int i = 0; i < 5; i++) {
		vals[i] = rand() % 10;
		printf("%d ", vals[i]);
	}
	printf("\n");

	INTEGER *values[5];
	for (int i = 0; i < 5; i++) {
		values[i] = newINTEGER(vals[i]);
	}

	printf("Inserting values...\n");

	for (int i = 0; i < 5; i++) {
		insertBST(tree, values[i]);
	}

	printf("Displaying tree...\n");
	displayBST(tree, stdout);

	return 0;

}