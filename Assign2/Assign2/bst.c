/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 2            * This file defines the implementations of   *
*             Wyatt Fairbanks               * the BST class methods.                     *
*             Dr. John Lusth                *                                            *
*             bst.c                         *                                            *
*             10/22/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"

struct bst {
	void (*swap)    (void *v1, void *v2);
	int  (*compare) (void *v1, void *v2);
	void (*display) (void *value, FILE *fp);
	void (*free)    (void *value);
	TNODE *root;
	int    size;
	int    debug;
};

//UTILITY FUNCTIONS ////////////////////////////////////////////////////////////////

void swapNodes(TNODE *val1, TNODE *val2) {
	void *temp = getTNODEvalue(val1);
	setTNODEvalue(val1, getTNODEvalue(val2));
	setTNODEvalue(val2, temp);
	return;
}

int isLeaf(TNODE *n) {
	if (getTNODEleft(n) == 0 && getTNODEright(n) == 0) {
		return 1;
	}
	return 0;
}

int min(int val1, int val2) {
	if (val1 > val2) {
		return val2;
	}
	if (val2 > val1) {
		return val1;
	}
}

int minDepth(TNODE *node) {
	if (node == 0) {
		return -1;
	}
	if (getTNODEleft(node) && getTNODEright(node)) {
		return min(minDepth(getTNODEleft(node)), minDepth(getTNODEright(node))) + 1;
	}
	return 0;
}

int max(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	if (val2 > val1) {
		return val2;
	}
}

int maxDepth(TNODE *node) {
	if (node == 0) {
		return -1;
	}
	if (isLeaf(node)) {
		return 0;
	}
	if (getTNODEleft(node) && !getTNODEright(node)) {
		return maxDepth(getTNODEleft(node)) + 1;
	}
	if (!getTNODEleft(node) && getTNODEright(node)) {
		return maxDepth(getTNODEright(node)) + 1;
	}
	if (getTNODEleft(node) && getTNODEright(node)) {
		return max(maxDepth(getTNODEleft(node)), maxDepth(getTNODEright(node))) + 1;
	}
	return 0;
}

void levelOrder(QUEUE *queue, TNODE *n) {
	int height = maxDepth(n);
	if (height == 1) {
		enqueue(queue, n);
		return;
	}
	if (getTNODEleft(n)) {
		levelOrder(queue, getTNODEleft(n));
	}
	if (getTNODEright(n)) {
		levelOrder(queue, getTNODEright(n));
	}
}

//END UTILITY FUNCS ////////////////////////////////////////////////////////////////

BST *newBST(int(*c) (void *, void*)) {
	BST *tree     = malloc(sizeof(BST));
	tree->size    = 0;
	tree->debug   = 0;
	tree->swap    = swapNodes;
	tree->compare = c;
	tree->display = 0;
	tree->free    = 0;
	return tree;
}

void setBSTdisplay(BST *t, void (*d)(void *, FILE *)) {
	t->display = d;
	return;
}

void setBSTswapper(BST *t, void (*s)(void *, FILE *)) {
	t->swap = s;
	return;
}

void setBSTfree(BST *t, void(*f)(void *)) {
	t->free = f;
	return;
}

TNODE *getBSTroot(BST *t) {
	return t->root;
}

void setBSTroot(BST *t, TNODE *replacement) {
	t->root = replacement;
	return;
}

void setBSTsize(BST *t, int s) {
	t->size = s;
	return;
}

TNODE *insertBST(BST *t, void *value) {
	TNODE *node    = t->root;
	TNODE *newNode = newTNODE(value, 0, 0, 0);
	if (t->display) {
		setTNODEdisplay(newNode, t->display);
	}
	if (node == 0) {
		t->root = newNode;
		setBSTsize(t, 1);
		return newNode;
	}
	while (node != 0) {
		int c = t->compare(getTNODEvalue(node), value);
		if (c < 0 && getTNODEleft(node) == 0) {
			setTNODEleft(node, newNode);
			setBSTsize(t, t->size + 1);
			return newNode;
		}
		if (c > 0 && getTNODEright(node) == 0) {
			setTNODEright(node, newNode);
			setBSTsize(t, t->size + 1);
			return newNode;
		}
	}
}

void *findBST(BST *t, void *value) {
	TNODE *node = t->root;
	if (node == 0) {
		return NULL;
	}
	while (node != 0) {
		int c = t->compare(getTNODEvalue(node), value);
		if (c == 0) {
			return getTNODEvalue(node);
		}
		else {
			if (c < 0) {
				node = getTNODEleft(node);
			}
			if (c > 0) {
				node = getTNODEright(node);
			}
		}
	}
	return NULL;
}

TNODE *locateBST(BST *t, void *value) {
	TNODE *node = t->root;
	if (node == 0) {
		return NULL;
	}
	while (node != 0) {
		int c = t->compare(getTNODEvalue(node), value);
		if (c == 0) {
			return node;
		}
		else {
			if (c < 0) {
				node = getTNODEleft(node);
			}
			if (c > 0) {
				node = getTNODEright(node);
			}
		}
	}
	return NULL;
}

int deleteBST(BST *t, void *key) {
	TNODE *target = locateBST(t, key);
	if (target != NULL) {
		return -1;
	}
	target = swapToLeafBST(t, target);
	pruneLeafBST(t, target);
	if (t->free) {
		t->free(getTNODEvalue(target));
	}
	free(target);
	setBSTsize(t, t->size - 1);
	if (t->size == 0) {
		t->root = NULL;
	}
	return 0;
}

TNODE *swapToLeafBST(BST *t, TNODE *node) {
	if (isLeaf(node) == 1) {
		return node;
	}
	if (getTNODEleft(node)) {
		t->swap(node, getTNODEleft(node));
		node = getTNODEleft(node);
		while (getTNODEright(node)) {
			t->swap(node, getTNODEright(node));
			node = getTNODEright(node);
		}
		return swapToLeafBST(t, node);
	}
	else if (getTNODEright(node)) {
		t->swap(node, getTNODEright(node));
		node = getTNODEright(node);
		while (getTNODEleft(node)) {
			t->swap(node, getTNODEleft(node));
			node = getTNODEleft(node);
		}
		return swapToLeafBST(t, node);
	}
	return node;
}

void pruneLeafBST(BST *t, TNODE *leaf) {
	TNODE *parent = getTNODEparent(leaf);
	if (leaf == getTNODEleft(parent)) {
		setTNODEleft(parent, 0);
		return;
	}
	if (leaf == getTNODEright(parent)) {
		setTNODEright(parent, 0);
		return;
	}
}

int sizeBST(BST *t) {
	return t->size;
}

void statisticsBST(BST *t, FILE *fp) {
	int size = sizeBST(t);
	if (size == 0) {
		fprintf(fp, "Nodes: 0\nMinimum depth: -1\nMaximum depth: -1\n");
		return;
	}
	fprintf(fp, "Nodes: %d\nMinimum depth: %d\nMaximum depth: %d\n", size, minDepth(t->root), maxDepth(t->root));
	return;
}

void displayBST(BST *t, FILE *fp) {
	if (getBSTroot(t) == 0) {
		fprintf(fp, "0\n");
		return;
	}
	QUEUE *traversal = newQUEUE();
	if (t->debug == 1) {
		//in order
	}
	if (t->debug == 2) {
		//pre order
	}
	if (t->debug == 3) {
		//post order
	}
	levelOrder(traversal, getBSTroot(t));

	for (int i = 0; i < maxDepth(getBSTroot(t)); i++) {
		fprintf(fp, "0: ");
		t->display(dequeue(traversal), fp);
	}
	return;
}