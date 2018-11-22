#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"
#include "gst.h"
#include "rbt.h"
#include "tnode.h"
#include "integer.h"
#include "string.h"
#include "real.h"
#include "scanner.h"

char *cleanString(char *);
char *getString(FILE *);

int main(int argc, char **argv) {
	int rbt = 1, gst = 0;
	int cor, com;
	FILE *corpus, *commands;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-v") == 0) {
			printf("Written by Ben Gerszewski\n");
			return 0;
		}
	}
	if (argc == 3) {
		cor = 1;
		com = 2;
	}
	else if (argc == 4) {
		cor = 2;
		com = 3;
		if (strcmp(argv[1], "-g") == 0) {
			rbt = 0;
			gst = 1;
		}
		else if (strcmp(argv[1], "-r") == 0) {
			rbt = 1;
			gst = 0;
		}
		else
			return 0;
	}
	else
		return 0;
	corpus = fopen(argv[cor], "r");
	if (corpus == NULL) {
		printf("File '%s' not found\n", argv[cor]);
		return 1;
	}
	commands = fopen(argv[com], "r");
	if (commands == NULL) {
		printf("File '%s' not found\n", argv[com]);
		return 1;
	}
	RBT *rtree;
	GST *gtree;
	if (rbt) {
		rtree = newRBT(compareSTRING);
		setRBTdisplay(rtree, displaySTRING);
		setRBTfree(rtree, freeSTRING);
		char *string, *word;
		void *toDelete;
		int result;
		string = getString(corpus);
		while (!feof(corpus) || string) {
			if (string != 0 && strlen(string) > 0) {
				if (strcmp(string, "n") == 0) {
					//displayRBT(rtree, stdout);
					fflush(stdout);
				}
				insertRBT(rtree, newSTRING(string));
				//free(string); //<----------
			}
			string = getString(corpus);
		}
		if (string) {
			insertRBT(rtree, newSTRING(string));
			//free(string); //<-------------
		}
		char command;
		command = readChar(commands);
		while (!feof(commands) || command) {
			if (command) {
				switch (command) {
				case 'i' :
					word = getString(commands);
					if (word != 0 && strlen(word) > 0) {
						insertRBT(rtree, newSTRING(word));
						//free(word); //<-------------
					}
					break;
				case 'd' :
					word = getString(commands);
					if (word != 0 && strlen(word) > 0) {
						toDelete = newSTRING(word);
						result = deleteRBT(rtree, toDelete);
						if (result == -1)
							printf("Value %s not found.\n", word);
						//freeSTRING(toDelete);
						//free(word);
					}
					break;
				case 's' :
					sizeRBT(rtree) ? displayRBT(rtree, stdout) : printf("EMPTY\n");
					break;
				case 'r' :
					statisticsRBT(rtree, stdout);
					break;
				default :
					break;
				}
			}
			command = readChar(commands);
			if (command == EOF) break;
		}
		freeRBT(rtree);
	}
	else if (gst) {
		gtree = newGST(compareSTRING);
		setGSTdisplay(gtree, displaySTRING);
		setGSTfree(gtree, freeSTRING);
		char *string, *word;
		void *toDelete;
		int result;
		string = getString(corpus);
		while (!feof(corpus) || string) {
			if (string) {
				if (insertGST(gtree, newSTRING(string)) == NULL) {
					//free(string);
				}
				//free(string); //<-------------
			}
			string = getString(corpus);
		}
		if (string) {
			insertGST(gtree, newSTRING(string));
			//free(string); //<-------------
		}
		char command;
		command = readChar(commands);
		while (!feof(commands) || command) {
			if (command) {
				switch (command) {
				case 'i':
					word = getString(commands);
					if (word) {
						insertGST(gtree, newSTRING(word));
						//free(word); //<-------------
					}
					break;
				case 'd':
					word = getString(commands);
					if (word) {
						toDelete = newSTRING(word);
						result = deleteGST(gtree, toDelete);
						if (result == -1)
							printf("Value %s not found.\n", word);
						freeSTRING(toDelete);
						//free(word);
					}
					//check return and print error message potentially
					break;
				case 's':
					sizeGST(gtree) ? displayGST(gtree, stdout) : printf("EMPTY\n");
					break;
				case 'r':
					statisticsGST(gtree, stdout);
					break;
				default:
					break;
				}
			}
			command = readChar(commands);
			if (command == EOF) break;
			//printf("%d\n", command);
		}
		freeGST(gtree);
	}
	fclose(corpus);
	fclose(commands);
	return 0;
}

char *cleanString(char *string) {
	if (strlen(string) == 0 || string == NULL) {
		printf("\n\tSent an empty string to cleanString somehow\n");
		return NULL;
	}
	char *output = malloc((int)strlen(string) + 1);
	int j = 0;
	int hasAlpha = 0;
	for (int i = 0; i < (int)strlen(string); ++i) {
		if (isalpha(string[i])) {
			output[j++] = tolower(string[i]);
			hasAlpha = 1;
		}
		else if (i != ((int)strlen(string) - 1) && isspace(string[i]) && isalpha(string[i + 1]) && hasAlpha)
			output[j++] = ' ';
	}
	//free(string);
	output[j] = '\0';
	return output;
}

char *getString(FILE *fp) {
	char *string = NULL;
	char *newString = NULL;
	if (!feof(fp)) {
		if (stringPending(fp) != 0)
			string = readString(fp);
		else
			string = readToken(fp);
	}
	if (string != 0 && strlen(string) > 0) {
		newString = cleanString(string);
		free(string);
	}
	if (newString == NULL || strlen(newString) == 0) {
		if (string != NULL) //free(string);
		return NULL;
	}
	return newString;
}