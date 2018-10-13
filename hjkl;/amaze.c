/*****************************************************************************************
*                                           *                                            *
*             CS201-001 Assign 1            * This file contains the primary operations  *
*             Wyatt Fairbanks               * of the maze program.                       *
*             Dr. John Lusth                *                                            *
*             amaze.c                       *                                            *
*             10/02/2018                    *                                            *
*                                           *                                            *
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int main(int argc, char ** argv) {
	int optV = 0;
	int optS = 0;
	int optC = 0;
	int optR = 0;
	int optD = 0;
	
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) {
			optV = i;
		}
		if (strcmp(argv[i], "-s") == 0) {
			optS = i;
		}
		if (strcmp(argv[i], "-c") == 0) {
			optC = i;
		}
		if (strcmp(argv[i], "-r") == 0) {
			optR = i;
		}
		if (strcmp(argv[i], "-d") == 0) {
			optD = i;
		}
	}

	if (optV > 0) {
		printf("Written by Wyatt Fairbanks");
	}
	if (optC > 0) {
		MAZE *maze = newMAZE(atoi(argv[optC + 1]), atoi(argv[optC + 2]));
		/*
		createMAZE(maze);
		*/
		drawMAZE(maze, stdout);
	}

	return 0;

}