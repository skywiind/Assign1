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
	void (*swap)    (TNODE *v1, TNODE *v2);
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
	if (!n) {
		return 0;
	}
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
	return -1;
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
	return -1;
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

int isLeftChild(TNODE *n) {
	if (!n) {
		return 0;
	}
	if (getTNODEleft(getTNODEparent(n)) == n) {
		return 1;
	}
	return 0;
}

int isRightChild(TNODE *n) {
	if (!n) {
		return 0;
	}
	if (getTNODEright(getTNODEparent(n)) == n) {
		return 1;
	}
	return 0;
}

void levelOrderDisplay(TNODE *n, FILE *fp) {
	QUEUE *queue = newQUEUE();
	TNODE *temp = n;
	int i = 0;
	int l = 0;
	int c = 1;
	while (l != maxDepth(n) + 2) {
		if (i == 0) {
			fprintf(fp, "%d : ", l);
			l++;
		}
		else if (i == c) {
			fprintf(fp, "\n%d : ", l);
			c *= 2;
			l++;
			i = 0;
		}
		if (temp) {
			if (isLeaf(temp) == 1) {
				fprintf(fp, "=");
			}
			displayTNODE(temp, fp);
			fprintf(fp, "(");
			displayTNODE(getTNODEparent(temp), fp);
			fprintf(fp, ")");
			if (i == 0 && l == 1) {
				fprintf(fp, "X ");
			}
			else if (isLeftChild(temp) == 1) {
				fprintf(fp, "L ");
			}
			else if (isRightChild(temp) == 1) {
				fprintf(fp, "R ");
			}
			enqueue(queue, getTNODEleft(temp));
			enqueue(queue, getTNODEright(temp));
		}
		else {
			enqueue(queue, NULL);
			enqueue(queue, NULL);
		}
		temp = dequeue(queue);
		i++;
	}
	freeQUEUE(queue);
	return;
}

void inOrderDisplay(BST *t, TNODE *n, FILE *fp) {
	if (getTNODEleft(n)) {
		fprintf(fp, "[");
		inOrderDisplay(t, getTNODEleft(n), fp);
		fprintf(fp, "] ");	
	}
	if (n) {
		setTNODEdisplay(n, t->display);
		displayTNODE(n, fp);
	}
	if (getTNODEright(n)) {
		fprintf(fp, " [");
		inOrderDisplay(t, getTNODEright(n), fp);
		fprintf(fp, "]");
	}
}

void preOrderDisplay(BST *t, TNODE *n, FILE *fp) {
	if (n) {
		setTNODEdisplay(n, t->display);
		displayTNODE(n, fp);
	}
	if (getTNODEleft(n)) {
		fprintf(fp, " [");
		preOrderDisplay(t, getTNODEleft(n), fp);
		fprintf(fp, "]");
	}
	if (getTNODEright(n)) {
		fprintf(fp, " [");
		preOrderDisplay(t, getTNODEright(n), fp);
		fprintf(fp, "]");
	}
}

void postOrderDisplay(BST *t, TNODE *n, FILE *fp) {
	if (getTNODEleft(n)) {
		fprintf(fp, "[");
		postOrderDisplay(t, getTNODEleft(n), fp);
		fprintf(fp, "] ");
	}
	if (getTNODEright(n)) {
		fprintf(fp, "[");
		postOrderDisplay(t, getTNODEright(n), fp);
		fprintf(fp, "] ");
	}
	if (n) {
		setTNODEdisplay(n, t->display);
		displayTNODE(n, fp);
	}
}

void postOrderFree(BST *t, TNODE *n) {
	if (getTNODEleft(n)) {
		postOrderFree(t, getTNODEleft(n));
	}
	if (getTNODEright(n)) {
		postOrderFree(t, getTNODEright(n));
	}
	if (n) {
		setTNODEfree(n, t->free);
		freeTNODE(n);
	}
}

//END UTILITY FUNCS ////////////////////////////////////////////////////////////////

BST *newBST(int(*c) (void *, void*)) {
	BST *tree     = malloc(sizeof(BST));
	tree->root    = 0;
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

void setBSTswapper(BST *t, void (*s)(TNODE *, TNODE *)) {
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
		setTNODEparent(newNode, newNode);
		t->root = newNode;
		setBSTsize(t, 1);
		return newNode;
	}
	while (node != 0) {
		int c = t->compare(getTNODEvalue(node), value);
		if (c > 0 && getTNODEleft(node) == 0) {
			setTNODEleft(node, newNode);
			setTNODEparent(newNode, node);
			setBSTsize(t, t->size + 1);
			return newNode;
		}
		if (c < 0 && getTNODEright(node) == 0) {
			setTNODEright(node, newNode);
			setTNODEparent(newNode, node);
			setBSTsize(t, t->size + 1);
			return newNode;
		}
		if (c > 0) {
			node = getTNODEleft(node);
		}
		if (c < 0) {
			node = getTNODEright(node);
		}
		if (c == 0) {
			return NULL;
		}
	}
	return NULL;
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
	if (getBSTroot(t) == leaf) {
		return;
	}	
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

	if (t->debug > 0 && t->root == NULL) {
		fprintf(fp, "[]\n");
		return;
	}
	else if (t->debug == 1) {
		fprintf(fp, "[");
		inOrderDisplay(t, t->root, fp);
		fprintf(fp, "]\n");
	}
	else if (t->debug == 2) {
		fprintf(fp, "[");
		preOrderDisplay(t, t->root, fp);
		fprintf(fp, "]\n");
	}
	else if (t->debug == 3) {
		fprintf(fp, "[");
		postOrderDisplay(t, t->root, fp);
		fprintf(fp, "]\n");
	}
	else {
		levelOrderDisplay(getBSTroot(t), fp);
	}
	return;
}

int debugBST(BST *t, int level) {
	int temp = t->debug;
	t->debug = level;
	return temp;
}

void freeBST(BST *t) {
	postOrderFree(t, t->root);
	free(t);
}