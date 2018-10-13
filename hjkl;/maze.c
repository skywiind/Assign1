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
#include "stack.h"

struct maze {
	CELL ***arr;
	int     h;
	int     w;
};

MAZE * newMAZE(int h, int w) {
	MAZE * maze = malloc(sizeof(MAZE));
	maze->arr = malloc(sizeof(CELL **) * maze->h);
	for (int i = 0; i < h; i++) {
		maze->arr[i] = malloc(sizeof(CELL *) * maze->w);
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

int neighbors(MAZE * maze, CELL * cell, CELL **adjacent) {
	int row = getRow(cell);
	int col = getCol(cell);
	int count = 0;
	if (cellUCheck(maze, cell)) {
		adjacent[count] = cellUCheck(maze, cell);
		count++;
	}
	if (cellDCheck(maze, cell)) {
		adjacent[count] = cellDCheck(maze, cell);
		count++;
	}
	if (cellLCheck(maze, cell)) {
		adjacent[count] = cellLCheck(maze, cell);
		count++;
	}
	if (cellRCheck(maze, cell)) {
		adjacent[count] = cellRCheck(maze, cell);
		count++;
	}
	return count;
}

CELL * goUp(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (row - 1 < 0) {
		return NULL;
	}
	return maze->arr[row - 1][col];
}

CELL * goDown(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (row + 1 < maze->h) {
		return NULL;
	}
	return maze->arr[row + 1][col];
}

CELL * goLeft(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (col - 1 < 0) {
		return NULL;
	}
	return maze->arr[row][col - 1];
}

CELL * goRight(MAZE * maze, CELL * cell) {
	int row = getRow(cell);
	int col = getCol(cell);
	if (col + 1 < maze->h) {
		return NULL;
	}
	return maze->arr[row][col + 1];
}

void rightWall(CELL * cell) {
	setCELL(cell, getBWall(cell), 1);
	return;
}

void bottomWall(CELL * cell) {
	setCELL(cell, 1, getRWall(cell));
	return;
}

void removeWall(MAZE * maze, CELL * curr, CELL * next) {
	if (getRow(curr) == getRow(next)) {
		getCol(curr) < getCol(curr) ? rightWall(curr) : rightWall(next);
	}
	else {
		getRow(curr) < getRow(next) ? bottomWall(curr) : bottomWall(next);
	}
	return;
}

//function for drawing top and bottoms
void drawEnds(MAZE * maze, FILE * fp) {
	int cols = maze->w;
	int dash = (4 * cols) + 1;
	for (int i = 0; i < dash; i++) {
		fprintf(fp, "-");
	}
	fprintf(fp, "\n");
}

//function for drawing vertical walls
void drawWalls(MAZE * maze, FILE * fp, int row) {
	int cols = maze->w;
	for (int i = 0; i < cols; i++) {
		if (row == 0 && i == 0) {
			fprintf(fp, " ");
		}
		if (row != 0 && i == 0) {
			fprintf(fp, "|");
		}
		if (getStep(maze->arr[row][i]) == -1) {
			fprintf(fp, "   ");
		}
		else {
			fprintf(fp, " %d ", (getStep(maze->arr[row][i]) % 10));
		}		
		if (getRWall(maze->arr[row][i]) == 0) {
			if (row == maze->h && i == cols) {
				fprintf(fp, " ");
			}
			else {
				fprintf(fp, "|");
			}
		}
		else {
			fprintf(fp, " ");
		}
	}
	fprintf(fp, "\n");

	for (int i = 0; i < cols; i++) {
		fprintf(fp, "-");
		if (getBWall(maze->arr[row][i]) == 0) {
			fprintf(fp, "---");
		}
		else {
			fprintf(fp, "   ");
		}
		fprintf(fp, "-");
	}
	fprintf(fp, "\n");
}


//END UTILITY FUNCTIONS/////////////////////////////////////////////////////

void createMAZE(MAZE * maze) {
	STACK * stack = newSTACK();
	CELL *  curr  = maze->arr[0][0];
	CELL *  adjacent[3];
	int     choice = 0;
	int     count  = 0;
	push(stack, curr);
	while (sizeSTACK(stack) != 0) {
		curr = peekSTACK(stack);
		if (checkCELL(curr) == 0) {
			visitCELL(curr);
			count = neighbors(maze, curr, adjacent);
			choice = random() % count;
			removeWall(maze, curr, adjacent[choice]);
			push(stack, adjacent[choice]);
		}
		else {
			pop(stack);
		}
	}
	freeSTACK(stack);
	return;
}

void solveMAZE(MAZE * maze) {
	return;
}

void writeMAZE(MAZE * maze, FILE * fp) {
	return;
}


void drawMAZE(MAZE * maze, FILE * fp) {
	drawEnds(maze, fp);
	for (int i = 0; i < maze->h; i++) {
		drawWalls(maze, fp, i);
	}
	return;
}
