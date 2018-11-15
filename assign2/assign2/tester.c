#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "gst.h"
#include "rbt.h"
#include "tnode.h"
#include "integer.h"
#include "string.h"
#include "real.h"

#define TREESIZE 5
#define USERBT
#define STRING

#ifdef USERBT
#define STRUCTURE RBT
#define insertSTRUCTURE insertRBT
#define statisticsSTRUCTURE statisticsRBT
#define displaySTRUCTURE displayRBT
#define debugSTRUCTURE debugRBT
#define newSTRUCTURE newRBT
#define setSTRUCTUREfree setRBTfree
#define setSTRUCTUREdisplay setRBTdisplay
#define deleteSTRUCTURE deleteRBT
#define freeSTRUCTURE freeRBT
#endif
#ifdef USEGST
#define STRUCTURE GST
#define insertSTRUCTURE insertGST
#define statisticsSTRUCTURE statisticsGST
#define displaySTRUCTURE displayGST
#define debugSTRUCTURE debugGST
#define newSTRUCTURE newGST
#define setSTRUCTUREfree setGSTfree
#define setSTRUCTUREdisplay setGSTdisplay
#define deleteSTRUCTURE deleteGST
#define freeSTRUCTURE freeGST
#endif
#ifdef USEBST
#define STRUCTURE BST
#define insertSTRUCTURE insertBST
#define statisticsSTRUCTURE statisticsBST
#define displaySTRUCTURE displayBST
#define debugSTRUCTURE debugBST
#define newSTRUCTURE newBST
#define setSTRUCTUREfree setBSTfree
#define setSTRUCTUREdisplay setBSTdisplay
#define deleteSTRUCTURE deleteBST
#define freeSTRUCTURE freeBST
#endif

#ifdef INTEGER
#define newDATA newINTEGER
#define displayDATA displayINTEGER
#define freeDATA freeINTEGER
#define compareDATA compareINTEGER
#endif
#ifdef REAL
#define newDATA newREAL
#define displayDATA displayREAL
#define freeDATA freeREAL
#define compareDATA compareREAL
#endif
#ifdef STRING
#define newDATA newSTRING
#define displayDATA displaySTRING
#define freeDATA freeSTRING
#define compareDATA compareSTRING
#endif

void displayTree(STRUCTURE *tree) {
	printf("\t~~~Displaying tree~~~\n");
	fflush(stdout);
	statisticsSTRUCTURE(tree, stdout);
	for (int i = 0; i < 4; ++i) {
		debugSTRUCTURE(tree, i);
		displaySTRUCTURE(tree, stdout);
		printf("\n");
	}
	printf("\n\n");
	return;
}

int main(void) {
	STRUCTURE *tree = newSTRUCTURE(compareDATA);
	setSTRUCTUREdisplay(tree, displayDATA);
	setSTRUCTUREfree(tree, freeDATA);
	debugSTRUCTURE(tree, 0);
	//int array[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3 };
	//int array[2] = { 5 };
#ifdef INTEGER
#define TREESIZE 12
	int array[12] = { 4, 4, 6, 1, 3, 5, 5, 0, 8, 9, 10, 11 };
	//int array[7] = { 4, 4, 6, 1, 3, 5, 5 };
#endif
	//int array[12] = { 16, 8, 4, 2, 1, 0, 17, 18, 19, 20, 21, 22 };
	//int array[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	//int array[12] = { 2, 1, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3 };
	//int array[12] = { 16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 18, 22 };
#ifdef STRING
#define TREESIZE 13
	char array[13][50] = { "the", "quickity quick", "brown", "fox", "jumped", "over", "the", "girl", "and", "her", "lazy", "lazy", "dog" };
#endif
	for (int i = 0; i < TREESIZE; ++i) {
		insertSTRUCTURE(tree, newDATA(array[i]));
	}
	displayTree(tree);
	//displayTree(tree);

	//for (int i = TREESIZE - 1; i >= 0; --i) {
	//  void *find = newINTEGER(array[i]);
	//  printf("Trying to delete (%d)\n", array[i]);
	//  int isGone = deleteSTRUCTURE(tree, find); //can't assert since delete returns freq
	//  displayTree(tree);
	//  if (isGone == -1) printf("\n\tCouldn't find the node (%d)\n", array[i]);
	//  else if (isGone == 0) printf("Removed (%d) from the tree\n", array[i]);
	//  else printf("(%d) was a duplicate and the frequency has been reduced to %d\n", array[i], isGone);
	//  freeINTEGER(find);
	//}

	freeSTRUCTURE(tree);
	return 0;
}