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

extern CELL *newCELL(int, int);
extern void  setCELL(CELL *, int, int);
extern int   getBWall(CELL *);
extern int   getRWall(CELL *);
extern int   getRow(CELL *);
extern int   getCol(CELL *);
extern void  visitCELL(CELL *);
extern int   checkCELL(CELL *);
extern void  freeCELL(CELL *);
extern void  drawCELL(CELL *);
extern void  writeCELL(CELL *, FILE *);

#endif