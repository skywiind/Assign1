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

void setBWall(CELL * cell, int b) {
	cell->b = b;
	return;
}

void setRWall(CELL * cell, int r) {
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

int getStep(CELL * cell) {
	return cell->step;
}

void freeCELL(CELL * cell) {
	free(cell);
	return;
}

void resetCELL(CELL * cell) {
	cell->vis = 0;
	cell->step = -1;
	return;
}

void visitCELL(CELL * cell) {
	cell->vis = 1;
	return;
}

int checkCELL(CELL * cell) {
	return cell->vis;
}

void stepCELL(CELL * cell, int value) {
	cell->step = value;
	return;
}