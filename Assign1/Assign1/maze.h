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

extern MAZE *newMAZE(int h, int w);
extern void  createMAZE(MAZE * maze);
extern void  solveMAZE(MAZE * maze);
extern void  writeMAZE(MAZE * maze, FILE * fp);
extern void  drawMAZE(MAZE * maze);
#endif