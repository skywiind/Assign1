/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 1            * This file declares the public methods for  *
*             Wyatt Fairbanks               * the cell class.                            *
*             Dr. John Lusth                *                                            *
*             cell.h                        *                                            *
*             10/02/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#ifndef __CELL_INCLUDED__
#define __CELL_INCLUDED__

#include <stdio.h>

typedef struct cell CELL;

extern CELL *newCELL(int row, int col);
extern void  setCELL(CELL * cell, int b, int r);
extern int   getBWall(CELL * cell);
extern int   getRWall(CELL * cell);
extern int   getRow(CELL * cell);
extern int   getCol(CELL * cell);
extern void  freeCELL(CELL *);

#endif