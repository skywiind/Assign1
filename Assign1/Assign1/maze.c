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
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			newCELL(i, j);
		}
	}
	maze->h = h;
	maze->w = w;
	return maze;
}



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
