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
#include "queue.h"

//Totally arbitrary declarations of random() and srandom() because rand() and srand() aren't good enough, I suppose.
extern void srandom(unsigned int);
extern long int random(void);

struct maze {
	CELL ***arr;
	int     h;
	int     w;
};

MAZE * newMAZE(int h, int w) {
	MAZE * maze = malloc(sizeof(MAZE));
	maze->h = h;
	maze->w = w;
	maze->arr = malloc(sizeof(CELL **) * maze->h);
	for (int i = 0; i < h; i++) {
		maze->arr[i] = malloc(sizeof(CELL *) * maze->w);
		for (int j = 0; j < w; j++) {
			maze->arr[i][j] = newCELL(i, j);
		}
	}
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
	if (row + 1 > maze->h - 1) {
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
	if (col + 1 > maze->w - 1) {
		return NULL;
	}
	if (checkCELL(maze->arr[row][col + 1]) == 1) {
		return NULL;
	}
	return maze->arr[row][col + 1];
}

int neighbors(MAZE * maze, CELL * cell, CELL **adjacent) {
	int count = 0;
	if (cellUCheck(maze, cell) != NULL) {
		adjacent[count] = cellUCheck(maze, cell);
		count++;
	}
	if (cellLCheck(maze, cell) != NULL) {
		adjacent[count] = cellLCheck(maze, cell);
		count++;
	}
	if (cellRCheck(maze, cell) != NULL) {
		adjacent[count] = cellRCheck(maze, cell);
		count++;
	}
	if (cellDCheck(maze, cell) != NULL) {
		adjacent[count] = cellDCheck(maze, cell);
		count++;
	}
	return count;
}

int BFSneighbors(MAZE * maze, CELL * cell, QUEUE * queue) {
	int count = 0;
	if (cellUCheck(maze, cell) && getBWall(cellUCheck(maze, cell))) {
		stepCELL(cellUCheck(maze, cell), getStep(cell) + 1);
		enqueue(queue, cellUCheck(maze, cell));
		count++;
	}
	if (cellLCheck(maze, cell) && getRWall(cellLCheck(maze, cell))) {
		stepCELL(cellLCheck(maze, cell), getStep(cell) + 1);
		enqueue(queue, cellLCheck(maze, cell));
		count++;
	}
	if (cellRCheck(maze, cell) && getRWall(cell)) {
		if (!(getRow(cell) == maze->h - 1 && getCol(cell) == maze->w - 1)) {
			stepCELL(cellRCheck(maze, cell), getStep(cell) + 1);
			enqueue(queue, cellRCheck(maze, cell));
			count++;
		}
	}
	if (cellDCheck(maze,cell) && getBWall(cell)) {
		stepCELL(cellDCheck(maze, cell), getStep(cell) + 1);
		enqueue(queue, cellDCheck(maze, cell));
		count++;
	}
	return count;
}

/*CELL * goUp(MAZE * maze, CELL * cell) {
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
}*/

void removeWall(CELL * curr, CELL * next) {
	if (getRow(curr) == getRow(next)) {
		getCol(curr) < getCol(next) ? setRWall(curr, 1) : setRWall(next, 1);
	}
	else {
		getRow(curr) < getRow(next) ? setBWall(curr, 1) : setBWall(next, 1);
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
		else if (i != cols) {
			fprintf(fp, "   ");
		}
		if (i == cols - 1) {
			fprintf(fp, "-");
		}
	}
	fprintf(fp, "\n");
}

void resetCells(MAZE * maze) {
	for (int i = 0; i < maze->h; i++) {
		for (int j = 0; j < maze->w; j++) {
			resetCELL(maze->arr[i][j]);
		}
	}
}

//END UTILITY FUNCTIONS/////////////////////////////////////////////////////

void createMAZE(MAZE * maze, int seed) {
	STACK * stack = newSTACK();
	CELL *  curr  = maze->arr[0][0];
	CELL *  adjacent[3];
	int     choice = 0;
	int     count  = 0;
	push(stack, curr);
	srandom(seed);
	while (sizeSTACK(stack) != 0) {
		curr = peekSTACK(stack);
		visitCELL(curr);
		count = neighbors(maze, curr, adjacent);
		if (count != 0) {
			choice = random() % count;
			removeWall(curr, adjacent[choice]);
			push(stack, adjacent[choice]);
		}
		else {
			pop(stack);
		}
	}
	setRWall(maze->arr[maze->h - 1][maze->w - 1], 1);
	freeSTACK(stack);
	return;
}

void solveMAZE(MAZE * maze) {
	resetCells(maze);
	QUEUE * queue = newQUEUE();
	CELL *  curr = maze->arr[0][0];
	enqueue(queue, curr);
	stepCELL(curr, 0);
	visitCELL(curr);
	while (!(getRow(curr) == maze->h - 1 && getCol(curr) == maze->w - 1)) {
		curr = dequeue(queue);
		visitCELL(curr);
		BFSneighbors(maze, curr, queue);
	}
	while (sizeQUEUE(queue) != 0) {
		curr = dequeue(queue);
		stepCELL(curr, -1);
	}
	freeQUEUE(queue);
	return;
}

void writeMAZE(MAZE * maze, FILE * fp) {
	fprintf(fp, "%d %d\n", maze->h, maze->w);
	for (int i = 0; i < maze->h; i++) {
		for (int j = 0; j < maze->w; j++) {
			fprintf(fp, "%d ", getBWall(maze->arr[i][j]));
			fprintf(fp, "%d ", getRWall(maze->arr[i][j]));
			fprintf(fp, "%d\n", getStep (maze->arr[i][j]));
		}
	}
	return;
}


void drawMAZE(MAZE * maze, FILE * fp) {
	drawEnds(maze, fp);
	for (int i = 0; i < maze->h; i++) {
		drawWalls(maze, fp, i);
	}
	return;
}

MAZE * readMAZE(FILE * fp) {
	int h = 0;
	int w = 0;
	int b = 0;
	int r = 0;
	int s = 0;
	fscanf(fp, "%d %d", &h, &w);
	MAZE * maze = newMAZE(h, w);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			fscanf(fp, "%d %d %d", &b, &r, &s);
			setBWall(maze->arr[i][j], b);
			setRWall(maze->arr[i][j], r);
			stepCELL(maze->arr[i][j], s);
		}
	}
	return maze;
}

void freeMAZE(MAZE * maze) {
	for (int i = 0; i < maze->h; i++) {
		for (int j = 0; j < maze->w; j++) {
			freeCELL(maze->arr[i][j]);
		}
		free(maze->arr[i]);
	}
	free(maze->arr);
	free(maze);
	return;
}
