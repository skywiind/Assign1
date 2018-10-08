#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "integer.h"

/*
DA Test Suite
Version 2
Created by Lusth
Modified by Ben Gerszewski
*/

//#define LOOPSIZE 10000

#define IR1 0
#define IR2 0 /*sizeDA(d)-1*/ /*rand()%sizeDA(d)*/
#define I3 sizeDA(d)
#define R3 sizeDA(d)-1
int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Add loop size to command line arguments.\n");
		printf("Example: ./datest 5000\n");
		return 1;
	}
	int LOOPSIZE = atoi(argv[1]);
	int count = 0;
	srand(10);
	DA *d = newDA();
	setDAdisplay(d, displayINTEGER);
	setDAfree(d, freeINTEGER);
	printf("doing a bunch of inserts\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		insertDA(d, IR1, newINTEGER(rand() % 1000)); //insert front
		++count;
		insertDA(d, I3, newINTEGER(rand() % 1000)); //insert back
		++count;
	}
	printf("doing a bunch of random inserts\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		int index = IR2;
		insertDA(d, index, newINTEGER(rand() % 1000)); //mostly insert middle
		++count;
	}
	printf("size: %d\n", sizeDA(d));
	printf("randomly doing a bunch of inserts and deletes\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		int mode = rand() % 6;
		if (mode == 0) { //insert front
			insertDA(d, IR1, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 1) { //insert middle
			insertDA(d, IR2, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 2) { //insert back
			insertDA(d, I3, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 3 && count > 0) { //remove front
			freeINTEGER(removeDA(d, IR1));
			--count;
		}
		else if (mode == 4 && count > 0) { //remove middle
			freeINTEGER(removeDA(d, IR2));
			--count;
		}
		else if (count > 0) { //remove back
			freeINTEGER(removeDA(d, R3));
			--count;
		}
	}
	printf("size: %d\n", sizeDA(d));
	printf("doing a bunch of random removes\n");
	while (count > 10) {
		freeINTEGER(removeDA(d, IR2)); //remove middle
		--count;
	}
	printf("array d:");
	displayDA(d, stdout);
	printf("\n");
	freeDA(d);
	printf("DA freed\n");
	return 0;
}