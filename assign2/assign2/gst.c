/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 2            * This file defines the implementations of   *
*             Wyatt Fairbanks               * the GST class methods.                     *
*             Dr. John Lusth                *                                            *
*             gst.c                         *                                            *
*             10/22/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "gst.h"

struct gst {
	BST   *tree;
	void (*display) (void *value, FILE *fp);
	void (*free) (void *value);
	void (*swap) (TNODE *v1, TNODE *v2);
	int  (*compare) (void *v1, void *v2);
	int d;
};

typedef struct gnode GNODE;

struct gnode {
	void  *v;
	int    f;
	void (*display) (void *value, FILE *fp);
	void (*free) (void *value);
	int  (*compare) (void *v1, void *v2);
};

//UTILITY FUNCTIONS ////////////////////////////////////////////////////////////////

void displayGNODE(void *v, FILE *fp) {
	GNODE *temp = v;
	if (temp == NULL) {
		return;
	}
	temp->display(temp->v, fp);
	GNODE *test = temp->v;
	if (test->f > 1) {
		fprintf(fp, "<%d>", test->f);
	}
	/*
	if (temp->f > 1) {
		fprintf(fp, "<%d>", temp->f);
	}
	*/
	return;
}

int compareGNODE(void *v, void *w) {
	GNODE *a = v;
	GNODE *b = w;
	return b->compare(a->v, b->v);
}

void freeGNODE(void *n) {
	GNODE *temp = n;
	temp->free(temp->v);
	free(temp);
	return;
}

void swapper(TNODE *a, TNODE *b) {
	void *x = getTNODEvalue(a);
	void *y = getTNODEvalue(b);
	setTNODEvalue(a, y);
	setTNODEvalue(b, x);
	return;
}

//END UTILITY FUNCS ////////////////////////////////////////////////////////////////

GNODE *newGNODE(void *value) {
	GNODE *newNode = malloc(sizeof(GNODE));
	newNode->v = value;
	newNode->f = 1;
	return newNode;
}

GST *newGST(int(*c)(void *, void *)) {
	GST *newTree     = malloc(sizeof(GST));
	newTree->tree    = newBST(compareGNODE);
	setBSTdisplay(newTree->tree, displayGNODE);
	setBSTfree(newTree->tree, freeGNODE);
	newTree->display = 0;
	newTree->free    = 0;
	newTree->compare = c;
	newTree->swap    = swapper;
	newTree->d       = 0;
	return newTree;
}

void setGSTdisplay(GST *t, void(*d)(void *v, FILE *fp)) {
	t->display = d;
	return;
}

void setGSTswapper(GST *t, void(*s)(TNODE *, TNODE *)) {
	t->swap = s;
	setBSTswapper(t->tree, s);
	return;
}

void setGSTfree(GST *t, void(*f)(void *)) {
	t->free = f;
	return;
}

TNODE *getGSTroot(GST *t) {
	return getBSTroot(t->tree);
}

void setGSTroot(GST *t, TNODE *replacement) {
	setBSTroot(t->tree, replacement);
	return;
}
void setGSTsize(GST *t, int s) {
	setBSTsize(t->tree, s);
	return;
}

TNODE *insertGST(GST *t, void *value) {
	GNODE *newNode   = newGNODE(value);
	newNode->display = t->display;
	newNode->compare = t->compare;
	newNode->free    = t->free;

	if (findBST(t->tree, newNode)) {
		TNODE *temp = locateGST(t, newNode);
		GNODE *unwrap = unwrapGST(temp);
		unwrap->f++;
		t->d++;
		freeGNODE(newNode);
		return temp;
	}

	return insertBST(t->tree, newNode);
}

void *findGST(GST *t, void *key) {
	return unwrapGST(findBST(t->tree, key));
}

TNODE *locateGST(GST *t, void *key) {
	return locateBST(t->tree, key);
}

int deleteGST(GST *t, void *key) {
	GNODE *temp = unwrapGST(locateGST(t, key));
	if (temp == 0) {
		return -1;
	}
	if (temp->f > 1) {
		temp->f--;
		return temp->f;
	}
	else {
		return deleteBST(t->tree, key);
	}
	return -1;
}

TNODE *swapToLeafGST(GST *t, TNODE *node) {
	return swapToLeafBST(t->tree, node);
}

void pruneLeafGST(GST *t, TNODE *leaf) {
	return pruneLeafBST(t->tree, leaf);
}

int sizeGST(GST *t) {
	return sizeBST(t->tree);
}

void statisticsGST(GST *t, FILE *fp) {
	fprintf(fp, "Duplicates: %d\n", t->d);
	statisticsBST(t->tree, fp);
	return;
}

void displayGST(GST *t, FILE *fp) {
	displayBST(t->tree, fp);
	return;
}

void freeGST(GST *t) {
	freeBST(t->tree);
	free(t);
	return;
}

int debugGST(GST *t, int level) {
	return debugBST(t->tree, level);
}

void *unwrapGST(TNODE *node) {
	if (!node) {
		return NULL;
	}
	GNODE *temp = getTNODEvalue(node);
	return temp->v;
}

int freqGST(GST *g, void *key) {
	TNODE *temp = locateGST(g, key);
	if (temp) {
		GNODE *unwrap = getTNODEvalue(temp);
		return unwrap->f;
	}
	return 0;
}

int duplicatesGST(GST *g) {
	return g->d;
}