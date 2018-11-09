/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 2            * This file defines the implementations of   *
*             Wyatt Fairbanks               * the RBT class methods.                     *
*             Dr. John Lusth                *                                            *
*             rbt.c                         *                                            *
*             10/22/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "gst.h"
#include "rbt.h"

//RED   = 0
//BLACK = 1

struct rbt {
	GST   *tree;
	void (*display) (void *v, FILE *fp);
	void (*free) (void *v);
	void (*swap) (TNODE *v1, TNODE* v2);
	int  (*compare) (void *v1, void *v2);
};

typedef struct rbnode RBNODE;

struct rbnode {
	void *v;
	int   c;
	void(*display) (void *value, FILE *fp);
	void(*free) (void *value);
	int(*compare) (void *v1, void *v2);
};

//UTILITY FUNCTIONS ////////////////////////////////////////////////////////////////

void displayRBNODE(void *v, FILE *fp) {
	RBNODE *temp = v;
	if (temp == NULL) {
		return;
	}
	temp->display(temp->v, fp);
	return;
}

int compareRBNODE(void *v, void *w) {
	RBNODE *a = v;
	RBNODE *b = w;
	return  a->compare(a->v, b->v);
}

void freeRBNODE(void *n) {
	RBNODE *temp = n;
	temp->free(temp->v);
	free(temp);
	return;
}

void swapper(TNODE *a, TNODE *b) {
	void *va = getTNODEvalue(a);   //get the GST value
	void *vb = getTNODEvalue(b);   //get the GST value
	// swap the GST values
	setTNODEvalue(a, vb);
	setTNODEvalue(b, va);
	// the above swap swapped the colors,
	// but the colors should stay with the nodes,
	// so swap the colors back to the original nodes
	RBNODE *x = unwrapGST(a);
	RBNODE *y = unwrapGST(b);
	int color = x->c;
	x->c = y->c;
	y->c = color;
	return;
}

void setNodeColor(TNODE *n, int color) {
	RBNODE *temp = unwrapGST(n);
	temp->c = color;
	return;
}

int getNodeColor(TNODE *n) {
	RBNODE *temp = unwrapGST(n);
	return temp->c;
}

int isNodeLeft(TNODE *n) {
	if (!n) {
		return -1;
	}
	if (getTNODEleft(getTNODEparent(n)) == n) {
		return 1;
	}
	return 0;
}

int isNodeRight(TNODE *n) {
	if (!n) {
		return -1;
	}
	if (getTNODEright(getTNODEparent(n)) == n) {
		return 1;
	}
	return 0;
}

TNODE *getGrandparent(TNODE *n) {
	if (!n) {
		return NULL;
	}
	return getTNODEparent(getTNODEparent(n));
}

TNODE *getUncle(TNODE *n) {
	if (!n) {
		return NULL;
	}
	//Is the parent node a right or left child?
	if (getTNODEright(getGrandparent(n)) == getTNODEparent(n)) {
		return getTNODEleft(getGrandparent(n));
	}
	else if (getTNODEleft(getGrandparent(n)) == getTNODEparent(n)) {
		return getTNODEright(getGrandparent(n));
	}
}
TNODE *getSibling(TNODE *n) {
	if (!n) {
		return NULL;
	}
	if (isNodeRight(n) == 1) {
		return getTNODEleft(getTNODEparent(n));
	}
	else {
		return getTNODEright(getTNODEparent(n));
	}
}

TNODE *getNephew(TNODE *n) {
	if (!n) {
		return NULL;
	}
	if (isNodeRight(n) == 1) {
		return getTNODEright(getSibling(n));
	}
	else {
		return getTNODEleft(getSibling(n));
	}
}

void rotateLeft(RBT *t, TNODE* x) {
	TNODE *y = getTNODEright(x);
	setTNODEright(x, getTNODEleft(y));
	if (getTNODEleft(y) != NULL) {
		setTNODEparent(getTNODEleft(y), x);
	}
	setTNODEparent(y, getTNODEparent(x));
	if (getTNODEparent(x) == NULL) {
		setRBTroot(t, y);
	}
	else if (isNodeLeft(x)) {
		setTNODEleft(getTNODEparent(x), y);
	}
	else {
		setTNODEright(getTNODEparent(x), y);
	}
	setTNODEleft(y, x);
	setTNODEparent(x, y);
	return;
}

void rotateRight(RBT *t, TNODE *x) {
	TNODE *y = getTNODEleft(x);
	setTNODEleft(x, getTNODEright(y));
	if (getTNODEright(y) != NULL) {
		setTNODEparent(getTNODEright(y), x);
	}
	setTNODEparent(y, getTNODEparent(x));
	if (getTNODEparent(x) == NULL) {
		setRBTroot(t, y);
	}
	else if (isNodeRight(x)) {
		setTNODEright(getTNODEparent(x), y);
	}
	else {
		setTNODEleft(getTNODEparent(x), y);
	}
	setTNODEright(y, x);
	setTNODEparent(x, y);
	return;
}

void insertFixup(RBT *t, TNODE *inserted) {
	TNODE *x = inserted;
	while (getRBTroot(t) != x) {
		if (getNodeColor(getTNODEparent(x)) == 1) {
			break;
		}
		if (getNodeColor(getUncle(x)) == 0) {
			setNodeColor(getTNODEparent(x), 1);
			setNodeColor(getUncle(x), 1);
			setNodeColor(getGrandparent(x), 0);
			x = getGrandparent(x);
		}
		else {
			if (isNodeLeft(x) == isNodeLeft(getTNODEparent(x))) {
				rotateRight(t, x);
				x = getTNODEright(x);
			}
			else if (isNodeRight(x) == isNodeRight(getTNODEparent(x))) {
				rotateLeft(t, x);
				x = getTNODEleft(x);
			}
			setNodeColor(getTNODEparent(x), 1);
			setNodeColor(getGrandparent(x), 0);
			if (isNodeLeft(getTNODEparent(x)) == 1) {
				rotateRight(t, getTNODEparent(x));
			}
			else {
				rotateLeft(t, getTNODEparent(x));
			}
			break;
		}
	}
	setNodeColor(getRBTroot(t), 1);
}

void deleteFixup(RBT *t, TNODE *deleted) {

}

//END UTILITY FUNCS ////////////////////////////////////////////////////////////////

RBNODE *newRBNODE(void *value) {
	RBNODE *newNode = malloc(sizeof(RBNODE));
	newNode->v = value;
	newNode->c = 0;
	return newNode;
}

RBT *newRBT(int(*c)(void *, void*)) {
	RBT *newTree     = malloc(sizeof(RBT));
	newTree->tree    = newGST(compareRBNODE);
	setGSTdisplay(newTree->tree, displayRBNODE);
	setGSTfree(newTree->tree, freeRBNODE);
	newTree->display = 0;
	newTree->free    = 0;
	newTree->compare = c;
	newTree->swap    = swapper;
	return newTree;
}

void setRBTdisplay(RBT *t, void(*d)(void *v, FILE *fp)) {
	t->display = d;
	return;
}

void setRBTswapper(RBT *t, void(*s)(TNODE*, TNODE*)) {
	t->swap, s;
	setGSTswapper(t->tree, s);
	return;
}

void setRBTfree(RBT *t, void(*f)(void*)) {
	t->free = f;
	return;
}

TNODE *getRBTroot(RBT *t) {
	return getGSTroot(t->tree);
}

void setRBTroot(RBT *t, TNODE *replacement) {
	setGSTroot(t->tree, replacement);
	return;
}

void setRBTsize(RBT *t, int s) {
	setGSTsize(t->tree, s);
	return;
}

TNODE *insertRBT(RBT *t, void *v) {
	RBNODE *newNode  = newRBNODE(v);
	newNode->display = t->display;
	newNode->compare = t->compare;
	newNode->free    = t->free;
	TNODE *inserted = insertGST(t->tree, newNode);
	insertFixup(t, inserted);
	return inserted;
}

void *findRBT(RBT *t, void *key) {
	return unwrapRBT(findGST(t->tree, key));
}

TNODE *locateRBT(RBT *t, void *key) {
	return locateGST(t->tree, key);
}

int deleteRBT(RBT *t, void *key) {

}

void *unwrapRBT(TNODE *node) {
	RBNODE *temp = unwrapGST(node);
	return temp->v;
}