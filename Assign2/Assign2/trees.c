/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 2            * This file links the compenents of the tree *
*             Wyatt Fairbanks               * program, and serves to control all         *
*             Dr. John Lusth                * processes.                                 *
*             trees.c                       *                                            *
*             10/22/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"
#include "gst.h"
#include "bst.h"
#include "tnode.h"
#include "string.h"

/*#define TREESIZE 5
#define USERBT
#define INTEGER*/

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
#define freqSTRUCTURE freqRBT
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
#define freqSTRUCTURE freqGST
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
#define freqSTRUCTURE freqBST
#endif

char *sanitizeString(char *string) {

}

int main(int argc, char **argv) {
	if (argv[1] == "-v") {
		printf("Author: Wyatt Fairbanks\n");
		return 0;
	}

	FILE *corpus   = fopen(argv[2], "r");
	FILE *commands = fopen(argv[3], "r");

	

	return 0;
}