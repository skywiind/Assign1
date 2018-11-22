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
#include "queue.h"

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
		QUEUE *queue = newQUEUE();
		rtree = newRBT(compareSTRING);
		setRBTdisplay(rtree, displaySTRING);
		setRBTfree(rtree, freeSTRING);
		char *string, *word;
		void *toDelete;
		int result;
		string = getString(corpus);
		while (!feof(corpus) || string) {
			if (string) {
				enqueue(queue, string);
				toDelete = newSTRING(string);
				insertRBT(rtree, toDelete);
			}
			string = getString(corpus);
		}
		char command;
		command = readChar(commands);
		while (!feof(commands) || command) {
			if (command) {
				switch (command) {
				case 'i' :
					word = getString(commands);
					if (word) {
						enqueue(queue, word);
						toDelete = newSTRING(word);
						insertRBT(rtree, toDelete);
					}
					break;
				case 'd' :
					word = getString(commands);
					if (word) {
						enqueue(queue, word);
						toDelete = newSTRING(word);
						if (freqRBT(rtree, toDelete) > 1)
							deleteRBT(rtree, toDelete);
						else {
							STRING *x = findRBT(rtree, toDelete);
							setRBTfree(rtree, 0);
							result = deleteRBT(rtree, toDelete);
							if (result == -1)
								printf("Value %s not found.\n", word);
							setRBTfree(rtree, freeSTRING);
							freeSTRING(x);
						}
						freeSTRING(toDelete);
					}
					break;
				case 's' :
					sizeRBT(rtree) ? displayRBT(rtree, stdout) : printf("EMPTY\n");
					break;
				case 'r' :
					statisticsRBT(rtree, stdout);
					break;
				case 'f' :
					word = getString(commands);
					toDelete = newSTRING(word);
					printf("Frequency of %s: %d\n", word, freqRBT(rtree, toDelete));
					break;
				default :
					break;
				}
			}
			command = readChar(commands);
			if (command == EOF) break;
		}
		while (sizeQUEUE(queue)) {
			free((char *)dequeue(queue));
		}
		freeQUEUE(queue);
		freeRBT(rtree);
	}
	else if (gst) {
		QUEUE *queue = newQUEUE();
		gtree = newGST(compareSTRING);
		setGSTdisplay(gtree, displaySTRING);
		setGSTfree(gtree, freeSTRING);
		char *string, *word;
		void *toDelete;
		int result;
		string = getString(corpus);
		while (!feof(corpus) || string) {
			if (string) {
				enqueue(queue, string);
				toDelete = newSTRING(string);
				insertGST(gtree, toDelete);
			}
			string = getString(corpus);
		}
		char command;
		command = readChar(commands);
		while (!feof(commands) || command) {
			if (command) {
				switch (command) {
				case 'i':
					word = getString(commands);
					if (word) {
						enqueue(queue, word);
						toDelete = newSTRING(word);
						insertGST(gtree, toDelete);
					}
					break;
				case 'd':
					word = getString(commands);
					if (word) {
						enqueue(queue, word);
						toDelete = newSTRING(word);
						if (freqGST(gtree, toDelete) > 1)
							deleteGST(gtree, toDelete);
						else {
							STRING *x = findGST(gtree, toDelete);
							setGSTfree(gtree, 0);
							result = deleteGST(gtree, toDelete);
							if (result == -1)
								printf("Value %s not found.\n", word);
							setGSTfree(gtree, freeSTRING);
							freeSTRING(x);
						}
						freeSTRING(toDelete);
					}
					break;
				case 's':
					sizeGST(gtree) ? displayGST(gtree, stdout) : printf("EMPTY\n");
					break;
				case 'r':
					statisticsGST(gtree, stdout);
					break;
				case 'f' :
					word = getString(commands);
					toDelete = newSTRING(word);
					printf("Frequency of %s: %d\n", word, freqGST(gtree, toDelete));
					break;
				default:
					break;
				}
			}
			command = readChar(commands);
			if (command == EOF) break;
		}
		while (sizeQUEUE(queue)) {
			free((char *)dequeue(queue));
		}
		freeQUEUE(queue);
		freeGST(gtree);
	}
	fclose(corpus);
	fclose(commands);
	return 0;
}


char *cleanString(char *string) {
	int j = 0;
    int hasAlpha = 0;
	for (int i = 0; i < (int)strlen(string); ++i) {
		if (isalpha(string[i])) {
			string[j++] = tolower(string[i]);
			hasAlpha = 1;
		}
		else if (i != ((int)strlen(string) - 1) && isspace(string[i]) && isalpha(string[i + 1]) && hasAlpha)
			string[j++] = ' ';
	}
    string = realloc(string, j + 1);
	string[j] = '\0';
	return string;
}

char *getString(FILE *fp) {
	if (feof(fp)) return NULL;
    char *input;
    if (stringPending(fp) != 0)
        input = readString(fp);
    else
        input = readToken(fp);
    if (input == 0) return NULL;
    int hasAlpha = 0;
    for (int i = 0; i < (int)strlen(input); ++i) {
        if (isalpha(input[i])) {hasAlpha = 1; break;}
    }
    if (hasAlpha == 0) {
        free(input);
        return NULL;
    }
    input = cleanString(input);
    return input;
}