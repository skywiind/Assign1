#include <stdio.h>
#include <stdlib.h>
#include "cda.h"
#include "da.h"
#include "integer.h"
void testCDA(int loopSize, int seed, FILE * fp) {
	int count = 0;
	srand(seed);
	CDA* d = newCDA();
	CDA* c = newCDA();
	setCDAfree(d, freeINTEGER);
	setCDAfree(c, freeINTEGER);
	fp = fopen("cdaTest.txt", "a");
	fprintf(fp, "CDA test file: srand(%d) and loopSize: %d\n",seed, loopSize);
	printf("doing a bunch of inserts\n");
	for (int i = 0; i < loopSize; ++i) {
		insertCDAfront(d, newINTEGER(rand() % 1000));
		++count;
		insertCDAback(d, newINTEGER(rand() % 1000));
		++count;
	}
	printf("doing a bunch of random inserts\n");
	for (int i = 0; i < loopSize; ++i) {
		int index = rand() % sizeCDA(d);
		insertCDA(d, index, newINTEGER(rand() % 1000)); //mostly insert middle
		++count;
	}
	printf("size: %d\n", sizeCDA(d));
	printf("randomly doing a bunch of inserts and deletes\n");
	for (int i = 0; i < loopSize; ++i) {
		int mode = rand() % 6;
		if (mode == 0) { //insert back
			insertCDAback(d, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 1) { //insert middle
			insertCDA(d, rand() % sizeCDA(d), newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 2) { //insert front
			insertCDAfront(d, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 3 && count > 0) { //remove back
			freeINTEGER(removeCDAback(d));
			--count;
		}
		else if (mode == 4 && count > 0) { //remove middle
			freeINTEGER(removeCDA(d, rand() % sizeCDA(d)));
			--count;
		}
		else if (count > 0) { //remove front
			freeINTEGER(removeCDAfront(d));
			--count;
		}
	}
	printf("new size: %d\n", sizeCDA(d));
	printf("doing a bunch of random removes to 1000\n");
	while (count > 1000) {
		freeINTEGER(removeCDA(d, rand() % sizeCDA(d))); //remove middle
		--count;
	}

	printf("randomly doing a bunch of inserts and deletes and unions\n");
	for (int t = 0; t < 100; t++) {
		for (int i = 0; i < ((loopSize * (rand() % 5)) / (1+(rand() % 25))); ++i) {
			int mode = rand() % 6;
			if (mode == 0) { //insert back
				insertCDAback(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode == 1) { //insert middle
				insertCDA(d, rand() % sizeCDA(d), newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode == 2) { //insert front
				insertCDAfront(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode == 3 && count > 0) { //remove back
				freeINTEGER(removeCDAback(d));
				--count;
			}
			else if (mode == 4 && count > 0) { //remove middle
				freeINTEGER(removeCDA(d, rand() % sizeCDA(d)));
				--count;
			}
			else if (count > 0) { //remove front
				freeINTEGER(removeCDAfront(d));
				--count;
			}
		}
		for (int j = 0; j < ((loopSize * rand() % 5) / (1+(rand()) % 25)); ++j) {
			int mode1 = rand() % 6;
			if (mode1 == 0) { //insert back
				insertCDAback(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode1 == 1) { //insert middle
				insertCDA(d, rand() % sizeCDA(d), newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode1 == 2) { //insert front
				insertCDAfront(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode1 == 3 && count > 0) { //remove back
				freeINTEGER(removeCDAback(d));
				--count;
			}
			else if (mode1 == 4 && count > 0) { //remove middle
				freeINTEGER(removeCDA(d, rand() % sizeCDA(d)));
				--count;
			}
			else if (count > 0) { //remove front
				freeINTEGER(removeCDAfront(d));
				--count;
			}
		}
		unionCDA(d, c);
	}

	fprintf(fp, "debug 0, no display: \n");
	displayCDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "debug 1, no display: \n");
	debugCDA(d, 1);
	displayCDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "debug 1, display set: \n");
	setCDAdisplay(d, displayINTEGER);
	displayCDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "size: %d\n", sizeCDA(d));
	fprintf(fp, "union array size (should be 0): %d\n", sizeCDA(c));
	debugCDA(c, 1);
	fprintf(fp, "union array free space (debug val = 1): ");
	displayCDA(c, fp);
	fprintf(fp, "\n");
	double total = 0;
	while (sizeCDA(d) > 0) {
		void* temp = removeCDAback(d);
		total += getINTEGER(temp);
		freeINTEGER(temp);
	}
	fprintf(fp, "the total value of your array is: %f\n\n\n", total);
	freeCDA(d);
	freeCDA(c);
	printf("CDA freed\n");

	fclose(fp);
}

void testDA(int loopSize, int seed, FILE * fp) {
	int count = 0;
	srand(seed);
	DA* d = newDA();
	DA* c = newDA();
	setDAfree(d, freeINTEGER);
	setDAfree(c, freeINTEGER);
	fp = fopen("DATest.txt", "a");
	fprintf(fp, "DA test file: srand(%d) and loopSize: %d\n", seed, loopSize);
	printf("doing a bunch of inserts\n");
	for (int i = 0; i < loopSize; ++i) {
		insertDAback(d, newINTEGER(rand() % 1000));
		++count;
	}
	printf("doing a bunch of random inserts\n");
	for (int i = 0; i < loopSize; ++i) {
		int index = rand() % sizeDA(d);
		insertDA(d, index, newINTEGER(rand() % 1000)); //mostly insert middle
		++count;
	}
	printf("size: %d\n", sizeDA(d));
	printf("randomly doing a bunch of inserts and deletes\n");
	for (int i = 0; i < loopSize; ++i) {
		int mode = rand() % 6;
		if (mode == 0) { //insert back
			insertDAback(d, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 2) { //insert middle
			insertDA(d, rand() % sizeDA(d), newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 3 && count > 0) { //remove back
			freeINTEGER(removeDAback(d));
			--count;
		}
		else if (mode == 4 && count > 0) { //remove middle
			freeINTEGER(removeDA(d, rand() % sizeDA(d)));
			--count;
		}
	}
	printf("new size: %d\n", sizeDA(d));
	printf("doing a bunch of random removes to 1000\n");
	while (count > 1000) {
		freeINTEGER(removeDA(d, rand() % sizeDA(d))); //remove middle
		--count;
	}

	printf("randomly doing a bunch of inserts and deletes and unions\n");
	for (int t = 0; t < 100; t++) {
		for (int i = 0; i < ((loopSize * (rand() % 5)) / (1 + (rand() % 25))); ++i) {
			int mode = rand() % 4;
			if (mode == 0) { //insert back
				insertDAback(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode == 2) { //insert middle
				insertDA(d, rand() % sizeDA(d), newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode == 3 && count > 0) { //remove back
				freeINTEGER(removeDAback(d));
				--count;
			}
			else if (mode == 4 && count > 0) { //remove middle
				freeINTEGER(removeDA(d, rand() % sizeDA(d)));
				--count;
			}

		}
		for (int j = 0; j < ((loopSize * rand() % 5) / (1 + (rand()) % 25)); ++j) {
			int mode1 = rand() % 6;
			if (mode1 == 0) { //insert back
				insertDAback(d, newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode1 == 2) { //insert middle
				insertDA(d, rand() % sizeDA(d), newINTEGER(rand() % 1000));
				++count;
			}
			else if (mode1 == 3 && count > 0) { //remove back
				freeINTEGER(removeDAback(d));
				--count;
			}
			else if (mode1 == 4 && count > 0) { //remove middle
				freeINTEGER(removeDA(d, rand() % sizeDA(d)));
				--count;
			}
		}
		unionDA(d, c);
	}

	fprintf(fp, "debug 0, no display: \n");
	displayDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "debug 1, no display: \n");
	debugDA(d, 1);
	displayDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "debug 1, display set: \n");
	setDAdisplay(d, displayINTEGER);
	displayDA(d, fp);
	fprintf(fp, "\n\n");
	fprintf(fp, "size: %d\n", sizeDA(d));
	fprintf(fp, "union array size (should be 0): %d\n", sizeDA(c));
	debugDA(c, 1);
	fprintf(fp, "union array free space (debug val = 1): ");
	displayDA(c, fp);
	fprintf(fp, "\n");
	double total = 0;
	while (sizeDA(d) > 0) {
		void* temp = removeDAback(d);
		total += getINTEGER(temp);
		freeINTEGER(temp);
	}
	fprintf(fp, "the total value of your array is: %f\n\n\n", total);
	freeDA(d);
	freeDA(c);
	printf("DA freed\n");

	fclose(fp);
}
int count = 0;
int main(void) {
	   FILE * CDA_FILE;
	   FILE * DA_FILE;
	   testCDA(1, 100, CDA_FILE);
	   testCDA(1000, 100, CDA_FILE);
	   testCDA(25000, 25, CDA_FILE);

	   testDA(1, 100, DA_FILE);
	   testDA(1000, 100, DA_FILE);
	   testDA(25000, 25, DA_FILE);
return 0;
   }

/*

*/