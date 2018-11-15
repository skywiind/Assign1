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
	if (!n) {
		return NULL;
	}
	return n->v;
}

void setTNODEvalue(TNODE *n, void *replacement) {
	if (!n) {
		return;
	}
	n->v = replacement;
	return;
}

TNODE *getTNODEleft(TNODE *n) {
	if (!n) {
		return NULL;
	}
	return n->l;
}

/*
REMOVING THE NULL CHECK ON REPLACEMENT TO TRY AND FIX ROTATION. 6:55PM 11/10
*/
void setTNODEleft(TNODE *n, TNODE *replacement) {
	if (!n) {
		return;
	}
	n->l = replacement;
	return;
}

TNODE *getTNODEright(TNODE *n) {
	if (!n) {
		return NULL;
	}
	return n->r;
}

/*
REMOVING THE NULL CHECK ON REPLACEMENT TO TRY AND FIX ROTATION. 6:55PM 11/10
*/
void setTNODEright(TNODE *n, TNODE *replacement) {
	if (!n) {
		return;
	}
	n->r = replacement;
	return;
}

TNODE *getTNODEparent(TNODE *n) {
	if (!n) {
		return NULL;
	}
	return n->p;
}

/*
REMOVING THE NULL CHECK ON REPLACEMENT TO TRY AND FIX ROTATION. 6:55PM 11/10
*/
void setTNODEparent(TNODE *n, TNODE *replacement) {
	if (!n) {
		return;
	}
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