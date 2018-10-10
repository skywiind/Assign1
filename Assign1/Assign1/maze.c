/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 1            * This file contains the implementations of  *
*             Wyatt Fairbanks               * the methods for the maze class.            *
*             Dr. John Lusth                *                                            *
*             maze.c                        *                                            *
*             10/02/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "maze.h"

struct maze {
	CELL ***arr;
	int     h;
	int     w;
};

MAZE * newMAZE(int h, int w) {
	MAZE * maze = malloc(sizeof(MAZE));
	//allocate for ** rows
	for (int i = 0; i < h; i++) {
		//allocate for * cols
		for (int j = 0; j < w; j++) {
			maze->arr[i][j] = newCELL(i, j);
		}
	}
	maze->h = h;
	maze->w = w;
	return maze;
}

//UTILITY FUNCTIONS/////////////////////////////////////////////////////////

CELL * cellUCheck(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (row - 1 < 0) {
		return NULL;
	}
	if (checkCELL(maze->arr[row - 1][col]) == 1) {
		return NULL;
	}
	return maze->arr[row - 1][col];
}

CELL * cellDCheck(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (row + 1 < maze->h) {
		return NULL;
	}
	if (checkCELL(maze->arr[row + 1][col]) == 1) {
		return NULL;
	}
	return maze->arr[row + 1][col];
}

CELL * cellLCheck(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (col - 1 < 0) {
		return NULL;
	}
	if (checkCELL(maze->arr[row][col - 1]) == 1) {
		return NULL;
	}
	return maze->arr[row][col - 1];
}

CELL * cellRCheck(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (col + 1 < maze->h) {
		return NULL;
	}
	if (checkCELL(maze->arr[row][col + 1]) == 1) {
		return NULL;
	}
	return maze->arr[row][col + 1];
}

int neighbors(MAZE * maze, CELL * cell, CELL **candidates) {
	int row = getRow(cell);
	int col = getCol(cell);
	int count = 0;
	if (cellUCheck(maze, cell)) {
		candidates[count] = cellUCheck(maze, cell);
		count++;
	}
	if (cellDCheck(maze, cell)) {
		candidates[count] = cellUCheck(maze, cell);
		count++;
	}
	if (cellLCheck(maze, cell)) {
		candidates[count] = cellUCheck(maze, cell);
		count++;
	}
	if (cellRCheck(maze, cell)) {
		candidates[count] = cellUCheck(maze, cell);
		count++;
	}
	return count;
}

//END UTILITY FUNCTIONS/////////////////////////////////////////////////////

void createMAZE(MAZE * maze) {
	
	return;
}

void solveMAZE(MAZE * maze) {
	return;
}

void writeMAZE(MAZE * maze, FILE * fp) {
	return;
}

void drawMAZE(MAZE * maze) {
	
	return;
}
