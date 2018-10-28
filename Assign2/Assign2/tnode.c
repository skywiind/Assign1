/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 2            * This file defines the implementations of   *
*             Wyatt Fairbanks               * the TNODE class methods.                   *
*             Dr. John Lusth                *                                            *
*             tnode.c                       *                                            *
*             10/22/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tnode.h"

struct tnode {
	void  *v;
	TNODE *p;
	TNODE *r;
	TNODE *l;
	int    d;
	void (*display) (void *value, FILE *fp);
	void (*free) (void *value);
};

TNODE *newTNODE(void *v, TNODE *p, TNODE *r, TNODE *l) {
	TNODE *node = malloc(sizeof(TNODE));
	assert(node != 0);
	node->d = 0;
	node->display = 0;
	node->free = 0;
	node->v = v;
	node->p = p;
	node->r = r;
	node->l = l;
	return node;
}

void setTNODEdisplay(TNODE *n, void(*d)(void *value, FILE *fp)) {
	n->display = d;
	return;
}

void setTNODEfree(TNODE *n, void(*f)(void *value)) {
	n->free = f;
	return;
}

void *getTNODEvalue(TNODE *n) {
	return n->v;
}

void setTNODEvalue(TNODE *n, void *replacement) {
	n->v = replacement;
	return;
}

TNODE *getTNODEleft(TNODE *n) {
	return n->l;
}

void setTNODEleft(TNODE *n, TNODE *replacement) {
	n->l = replacement;
	return;
}

TNODE *getTNODEright(TNODE *n) {
	return n->r;
}

void setTNODEright(TNODE *n, TNODE *replacement) {
	n->r = replacement;
	return;
}

TNODE *getTNODEparent(TNODE *n) {
	return n->p;
}

void setTNODEparent(TNODE *n, TNODE *replacement) {
	n->p = replacement;
	return;
}

void displayTNODE(TNODE *n, FILE *fp) {
	if (n->display == NULL) {
		fprintf(fp, "&%p", n->v);
	}
	else if (n->d > 0){
		n->display(n->v, fp);
		fprintf(fp, "&%p", n->v);
	}
	else {
		n->display(n->v, fp);
	}
	return;
}

int debugTNODE(TNODE *n, int level) {
	int prev = n->d;
	n->d = level;
	return prev;
}

void freeTNODE(TNODE *n) {
	if (n->free != 0) {
		n->free(n->v);
	}
	free(n);
	return;
}