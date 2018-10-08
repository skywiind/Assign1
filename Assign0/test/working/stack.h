/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 0            * This file declares the public methods for  *
*             Wyatt Fairbanks               * the stack class.                           *
*             Dr. John Lusth                *                                            *
*             stack.h                       *                                            *
*             9/11/2018                     *                                            *
*                                           *                                            *
*****************************************************************************************/
#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>

typedef struct stack STACK;

extern STACK *newSTACK(void);
extern void  setSTACKdisplay(STACK *, void(*)(void *, FILE *));
extern void  setSTACKfree(STACK *, void(*)(void *));
extern void  push(STACK *items, void *value);
extern void  *pop(STACK *items);
extern void  *peekSTACK(STACK *items);
extern void  displaySTACK(STACK *items, FILE *fp);
extern int   debugSTACK(STACK *items, int level);
extern void  freeSTACK(STACK *items);
extern int   sizeSTACK(STACK *items);

#endif