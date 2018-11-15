///*****************************************************************************************
//*                                           *                                            *
//*             CS201-001 Assign 2            * This file links the compenents of the tree *
//*             Wyatt Fairbanks               * program, and serves to control all         *
//*             Dr. John Lusth                * processes.                                 *
//*             trees.c                       *                                            *
//*             10/22/2018                    *                                            *
//*                                           *                                            *
//*****************************************************************************************/
//#include <stdio.h>
//#include <stdlib.h>
//#include "rbt.h"
//#include "gst.h"
//#include "bst.h"
//#include "tnode.h"
//#include "string.h"
//
///*#define TREESIZE 5
//#define USERBT
//#define INTEGER*/
//
//#ifdef USERBT
//#define STRUCTURE RBT
//#define insertSTRUCTURE insertRBT
//#define statisticsSTRUCTURE statisticsRBT
//#define displaySTRUCTURE displayRBT
//#define debugSTRUCTURE debugRBT
//#define newSTRUCTURE newRBT
//#define setSTRUCTUREfree setRBTfree
//#define setSTRUCTUREdisplay setRBTdisplay
//#define deleteSTRUCTURE deleteRBT
//#define freeSTRUCTURE freeRBT
//#define freqSTRUCTURE freqRBT
//#endif
//#ifdef USEGST
//#define STRUCTURE GST
//#define insertSTRUCTURE insertGST
//#define statisticsSTRUCTURE statisticsGST
//#define displaySTRUCTURE displayGST
//#define debugSTRUCTURE debugGST
//#define newSTRUCTURE newGST
//#define setSTRUCTUREfree setGSTfree
//#define setSTRUCTUREdisplay setGSTdisplay
//#define deleteSTRUCTURE deleteGST
//#define freeSTRUCTURE freeGST
//#define freqSTRUCTURE freqGST
//#endif
//#ifdef USEBST
//#define STRUCTURE BST
//#define insertSTRUCTURE insertBST
//#define statisticsSTRUCTURE statisticsBST
//#define displaySTRUCTURE displayBST
//#define debugSTRUCTURE debugBST
//#define newSTRUCTURE newBST
//#define setSTRUCTUREfree setBSTfree
//#define setSTRUCTUREdisplay setBSTdisplay
//#define deleteSTRUCTURE deleteBST
//#define freeSTRUCTURE freeBST
//#define freqSTRUCTURE freqBST
//#endif
//
//int main(int argc, char **argv) {
//	if (argv[1] == "-v") {
//		printf("Author: Wyatt Fairbanks\n");
//		return 0;
//	}
//
//	FILE *corpus   = fopen(argv[2], "r");
//	FILE *commands = fopen(argv[3], "r");
//	int g = 0;
//	int r = 0;
//	if (argv[1] == "-g") {
//		#define USEGST
//		int g = 1;
//	}
//
//	if (argv[1] == "-r") {
//		#define USERBT
//		int r = 1;
//	}
//
//
//	if (!corpus) {
//		printf("Failed to open corpus.\n");
//		return -1;
//	}
//	if (!commands) {
//		printf("Failed to open commands.\n");
//		return -1;
//	}
//
//	if (feof(readChar(commands))) {
//		return 0;
//	}
//
//	BST *base = newBST(compareSTRING);
//	if (g == 1) {
//		GST *tree = newGST(compareSTRING);
//	}
//	if (r == 1) {
//		RBT *tree = newRBT(compareSTRING);
//	}
//
//	while (!feof(readToken(corpus))) {
//		insertBST(base, (void *)readToken(corpus));
//		return 0;
//	}
//
//	while (!feof(readChar(commands))) {
//		if (readChar(commands) == "i") {
//			if (g == 1) {
//				insertGST(tree, (void *)readToken(commands));
//			}
//			if (r == 1) {
//				insertRBT(tree, (void *)readToken(commands));
//			}
//			continue;
//		}
//		if (readChar(commands) == "d") {
//			if (g == 1) {
//				deleteGST(tree, (void *)readToken(commands));
//			}
//			if (r == 1) {
//				deleteRBT(tree, (void *)readToken(commands));
//			}
//			continue;
//		}
//		if (readChar(commands) == "f") {
//			if (g == 1) {
//				freqGST(tree, (void *)readToken(commands));
//			}
//			if (r == 1) {
//				freqRBT(tree, (void *)readToken(commands));
//			}
//			continue;
//		}
//		if (readChar(commands) == "s") {
//			if (g == 1) {
//				displayGST(tree);
//			}
//			if (r == 1) {
//				displayRBT(tree);
//			}
//			continue;
//		}
//		if (readChar(commands) == "r") {
//			if (g == 1) {
//				statisticsGST(tree);
//			}
//			if (r == 1) {
//				statisticsRBT(tree);
//			}
//			continue;
//		}
//	}
//	return 0;
//}