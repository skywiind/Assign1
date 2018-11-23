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
	if (temp->c == 0) {
		fprintf(fp, "*");
	}
	return;
}

int compareRBNODE(void *v, void *w) {
	RBNODE *a = v;
	RBNODE *b = w;
	return  a->compare(a->v, b->v);
}

int compareShitstorm(void *v, void *w) {
	RBNODE *a = v;
	RBNODE *b = w;
	return  a->compare(a->v, b);
}

void freeRBNODE(void *n) {
	RBNODE *temp = n;
	temp->free(temp->v);
	free(temp);
	return;
}

void RBTswapper(TNODE *a, TNODE *b) {
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
	if (!n) {
		return;
	}
	RBNODE *temp = unwrapGST(n);
	temp->c = color;
	return;
}

int getNodeColor(TNODE *n) {
	if (!n) {
		return -1;
	}
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
	return NULL;
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
		return getTNODEleft(getSibling(n));
	}
	else {
		return getTNODEright(getSibling(n));
	}
}

TNODE *getNiece(TNODE *n) {
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

void rotateLeft(RBT *t, TNODE *b) {
	TNODE *a = NULL;
	TNODE *oldLeft = NULL;
	a = getTNODEparent(b);
	setTNODEparent(b, getTNODEparent(a));
	if (getRBTroot(t) != a) {
		if (isNodeLeft(a)) {
			setTNODEleft(getTNODEparent(a), b);
		}
		else {
			setTNODEright(getTNODEparent(a), b);
		}
	}

	oldLeft = getTNODEleft(b);
	setTNODEleft(b, a);
	setTNODEparent(a, b);
	setTNODEright(a, oldLeft);
	if (oldLeft != NULL) {
		setTNODEparent(oldLeft, a);
	}
	if (getRBTroot(t) == a) {
		setRBTroot(t, b);
		setTNODEparent(b, b);
	}
	return;
}

void rotateRight(RBT *t, TNODE *b) {
	TNODE *a = NULL;
	TNODE *oldRight = NULL;
	a = getTNODEparent(b);
	setTNODEparent(b, getTNODEparent(a));
	if (getRBTroot(t) != a) {
		if (isNodeLeft(a)) {
			setTNODEleft(getTNODEparent(a), b);
		}
		else {
			setTNODEright(getTNODEparent(a), b);
		}
	}

	oldRight = getTNODEright(b);
	setTNODEright(b, a);
	setTNODEparent(a, b);
	setTNODEleft(a, oldRight);
	if (oldRight != NULL) {
		setTNODEparent(oldRight, a);
	}
	if (getRBTroot(t) == a) {
		setRBTroot(t, b);
		setTNODEparent(b, b);
	}
	return;
}
/*
void rotateLeft(RBT *t, TNODE* x) {
	if (!x) {
		return;
	}
	int l = 0;
	if (!getTNODEright(x) && !getTNODEleft(x)) {
		l = 1;
	}
	TNODE *y = getTNODEright(x);
	setTNODEright(x, getTNODEleft(y));
	if (getTNODEleft(y)) {
		setTNODEparent(getTNODEright(x), x);
	}
	setTNODEparent(y, getTNODEparent(x));
	if (getTNODEparent(x) == x) {
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
	if (l != 0) {
		if (!getTNODEright(x) && !getTNODEleft(x)) {
			return;
		}
		else {
			printf("Error in rotation.\n");
		}
	}
	return;
}


void rotateRight(RBT *t, TNODE *x) {
	if (!x) {
		return;
	}
	int l = 0;
	TNODE *y = getTNODEleft(x);
	if(!getTNODEright(x) && !getTNODEleft(x)) {
		l = 1;
	}
	setTNODEleft(x, getTNODEright(y));
	if (getTNODEright(y)) {
		setTNODEparent(getTNODEleft(x), x);
	}
	setTNODEparent(y, getTNODEparent(x));
	if (getTNODEparent(x) == x) {
		setRBTroot(t, y);
	}
	else if (isNodeLeft(x)) {
		setTNODEleft(getTNODEparent(x), y);
	}
	else {
		setTNODEright(getTNODEparent(x), y);
	}
	setTNODEright(y, x);
	setTNODEparent(x, y);
	if (l != 0) {
		if (!getTNODEright(x) && !getTNODEleft(x)) {
			return;
		}
		else {
			printf("Error in rotation.\n");
		}
	}
	return;
}*/

void insertFixup(RBT *t, TNODE *inserted) {
	TNODE *x = inserted;
	//while x is not root
	while (getRBTroot(t) != x) {
		//if the parent is black
		if (getNodeColor(getTNODEparent(x)) == 1) {
			break;
		}
		//if the uncle is red
		if (getNodeColor(getUncle(x)) == 0) {
			//make the parent black
			setNodeColor(getTNODEparent(x), 1);
			//make the uncle black
			setNodeColor(getUncle(x), 1);
			//make the grandparent red
			setNodeColor(getGrandparent(x), 0);
			x = getGrandparent(x);
		}
		//the uncle is black
		else {
			//is the node the left child of a right child
			if (isNodeLeft(x)) {
				if (isNodeRight(getTNODEparent(x))) {
					rotateRight(t, x);
					x = getTNODEright(x);
				}
			}
			//is the node the right child of a left child
			else if (isNodeRight(x)) {
				if (isNodeLeft(getTNODEparent(x))) {
					rotateLeft(t, x);
					x = getTNODEleft(x);
				}
			}
			//make the parent black
			setNodeColor(getTNODEparent(x), 1);
			//make the grandparent red
			setNodeColor(getGrandparent(x), 0);
			//is the parent a left child
			if (isNodeLeft(getTNODEparent(x)) == 1) {
				rotateRight(t, getTNODEparent(x));
			}
			else {
				rotateLeft(t, getTNODEparent(x));
			}
			break;
		}
	}
	//recolor the root 
	setNodeColor(getRBTroot(t), 1);
	return;
}

void deleteFixup(RBT *t, TNODE *deleted) {
	TNODE *x = deleted;
	while (getRBTroot(t) != x) {
		if (getNodeColor(x) == 0) {
			break;
		}
		if (getNodeColor(getSibling(x)) == 0) {
			setNodeColor(getTNODEparent(x), 0);
			setNodeColor(getSibling(x), 0);
			if (isNodeLeft(getSibling(x)) == 1) {
				rotateRight(t, getSibling(x));
			}
			else {
				rotateLeft(t, getSibling(x));
			}
		}
		else if (getNodeColor(getNephew(x)) == 0) {
			setNodeColor(getSibling(x), getNodeColor(getTNODEparent(x)));
			setNodeColor(getTNODEparent(x), 1);
			setNodeColor(getNephew(x), 1);
			if (isNodeLeft(getSibling(x)) == 1) {
				rotateRight(t, getSibling(x));
			}
			else {
				rotateLeft(t, getSibling(x));
			}
			break;
		}
		else if (getNodeColor(getNiece(x)) == 0) {
			setNodeColor(getNiece(x), 1);
			setNodeColor(getSibling(x), 0);
			if (isNodeLeft(getNiece(x)) == 1) {
				rotateRight(t, getNiece(x));
			}
			else {
				rotateLeft(t, getSibling(x));
			}
		}
		else {
			setNodeColor(getSibling(x), 0);
			x = getTNODEparent(x);
		}
	}
	setNodeColor(x, 1);
	return;
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
	newTree->swap    = RBTswapper;
	return newTree;
}

void setRBTdisplay(RBT *t, void(*d)(void *v, FILE *fp)) {
	t->display = d;
	return;
}

void setRBTswapper(RBT *t, void(*s)(TNODE*, TNODE*)) {
	t->swap = s;
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
	int found = 0;
	TNODE* inserted = NULL;
	RBNODE *newNode  = newRBNODE(v);
	newNode->display = t->display;
	newNode->compare = compareShitstorm;
	newNode->free    = t->free;
	if (findGST(t->tree, newNode)) {
		found = 1;
	}
	
	newNode->compare = t->compare;
	inserted = insertGST(t->tree, newNode);

	if (!found) {
		insertFixup(t, inserted);
	}
	return inserted;
}

void *findRBT(RBT *t, void *key) {
	RBNODE *temp  = newRBNODE(key);
	temp->display = t->display;
	temp->compare = compareShitstorm;
	temp->free    = t->free;
	void *ans     = findGST(t->tree, temp);
	free(temp);
	return ans;
}

TNODE *locateRBT(RBT *t, void *key) {
	RBNODE *temp  = newRBNODE(key);
	temp->display = t->display;
	temp->compare = compareShitstorm;
	temp->free    = t->free;
	TNODE *ans    = locateGST(t->tree, temp);
	free(temp);
	return ans;
}

int deleteRBT(RBT *t, void *key) {
	TNODE *temp = locateRBT(t, key);
	if (!temp) {
		return -1;
	}
	int f = freqRBT(t, key);
	RBNODE *unwrap = unwrapGST(temp);
	if (f > 1) {
		deleteGST(t->tree, unwrap);
		return f - 1;
		/*RBNODE *target = newRBNODE(key);
		int ans = deleteGST(t->tree, target);
		free(target);
		return ans;*/
	}
	else {
		int size = sizeRBT(t);
		TNODE *node = swapToLeafGST(t->tree, temp);
		deleteFixup(t, node);
		pruneLeafGST(t->tree, node);
		setRBTsize(t, size - 1);
		return 0;
	}
	return -1;
}

TNODE *swapToLeafRBT(RBT *t, TNODE *node) {
	return swapToLeafGST(t->tree, node);
}

void pruneLeafRBT(RBT *t, TNODE *leaf) {
	return pruneLeafGST(t->tree, leaf);
}

int sizeRBT(RBT *t) {
	return sizeGST(t->tree);
}

void statisticsRBT(RBT *t, FILE *fp) {
	return statisticsGST(t->tree, fp);
}

void displayRBT(RBT *t, FILE *fp) {
	return displayGST(t->tree, fp);
}

void freeRBT(RBT *t) {
	freeGST(t->tree);
	free(t);
	return;
}

int debugRBT(RBT *t, int level) {
	return debugGST(t->tree, level);
}

void *unwrapRBT(TNODE *n) {
	if (!n) return NULL;
	RBNODE *temp = unwrapGST(n);
	return temp->v;
}

int freqRBT(RBT *g, void *key) {
	RBNODE *temp = newRBNODE(key);
	int freq = freqGST(g->tree, temp);
	free(temp);
	return freq;
}

/*int freqRBT(RBT *g, void *key) {
	TNODE *temp = locateRBT(g, key);
	if (temp) {
		RBNODE *unwrap = unwrapGST(temp);
	}
	return freqGST(g->tree, key);
}*/

int duplicatesRBT(RBT *g) {
	return duplicatesGST(g->tree);
}