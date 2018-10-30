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
};

struct GNODE {
	void *v;
	int   f;
};

GST *newGST(int(*c)(void *, void *)) {
	GST *newTree     = malloc(sizeof(GST));
	newTree->tree    = newBST(c);
	newTree->display = 0;
	newTree->free    = 0;
	newTree->compare = c;
	newTree->swap    = 0;
	return newTree;
}

void setGSTdisplay(GST *t, void(*d)(void *v, FILE *fp)) {
	t->display = d;
	setBSTdisplay(t->tree, d);
	return;
}

void setGSTswapper(GST *t, void(*s)(TNODE *, TNODE *)) {
	t->swap = s;
	setBSTswapper(t->tree, s);
	return;
}

void setGSTfree(GST *t, void(*f)(void *)) {
	t->free = f;
	setGSTfree(t->tree, f);
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