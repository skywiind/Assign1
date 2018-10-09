/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 1            * This file contains the implementations of  *
*             Wyatt Fairbanks               * the methods for the cell class.            *
*             Dr. John Lusth                *                                            *
*             cell.c                        *                                            *
*             10/02/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

struct cell {
	int b;
	int r;
	int row;
	int col;
	int vis;
	int step;
};

CELL * newCELL(int row, int col) {
	CELL *cell = malloc(sizeof(CELL));
	cell->b = 0;
	cell->r = 0;
	cell->row = row;
	cell->col = col;
	cell->vis = 0;
	cell->step = -1;
	return cell;
}

void setCELL(CELL * cell, int b, int r) {
	cell->b = b;
	cell->r = r;
	return;
}

int getBWall(CELL * cell) {
	return cell->b;
}

int getRWall(CELL * cell) {
	return cell->r;
}

int getRow(CELL * cell) {
	return cell->row;
}

int getCol(CELL * cell) {
	return cell->col;
}

void freeCELL(CELL * cell) {
	free(cell);
	return;
}

void drawCELL(CELL * cell) {

	return;
}

void writeCELL(CELL * cell, FILE * fp) {

	return;
}