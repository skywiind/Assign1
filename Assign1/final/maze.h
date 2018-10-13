/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 1            * This file declares the public methods for  *
*             Wyatt Fairbanks               * the maze class.                            *
*             Dr. John Lusth                *                                            *
*             maze.h                        *                                            *
*             10/02/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#ifndef __MAZE_INCLUDED__
#define __MAZE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>

typedef struct maze MAZE;

extern MAZE *newMAZE(int, int);
extern void  createMAZE(MAZE *, int);
extern void  solveMAZE(MAZE *);
extern void  writeMAZE(MAZE *, FILE *);
extern MAZE *readMAZE(FILE *);
extern void  drawMAZE(MAZE *, FILE *);
extern void  freeMAZE(MAZE *);

#endif