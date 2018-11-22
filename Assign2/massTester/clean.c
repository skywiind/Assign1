#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

char *cleanString(char *string);
char *getString(FILE *fp);

int main(int argc, char **argv) {
    FILE *corpus = fopen(argv[1], "r");
    FILE *commands = fopen(argv[2], "r");
    FILE *outCor = fopen("cleanCor.txt", "w");
    FILE *outCom = fopen("cleanCom.txt", "w");
    char *output = getString(corpus);
    while (!feof(corpus)) {
        if (output != NULL) {
            fprintf(outCor, "%s\n", output);
            free(output);
        }
        output = getString(corpus);
    }
    fclose(corpus);
    fclose(outCor);
    char command;
    command = readChar(commands);
    while (!feof(commands) || command) {
        if (command) {
            switch (command) {
                case 'i' :
                    output = getString(commands);
                    if (output != 0 && strlen(output) > 0) {
                        fprintf(outCom, "%c %s\n", command, output);
                        free(output);
                    }
                        //insertRBT(rtree, newSTRING(word));
                    break;
                case 'd' :
                    output = getString(commands);
                    if (output != 0 && strlen(output) > 0) {
                        fprintf(outCom, "%c %s\n", command, output);
                        free(output);
                        //result = deleteRBT(rtree, toDelete);
                        //if (result == -1)
                        //    printf("Value %s not found.\n", word);
                    }
                    break;
                case 's' :
                    fprintf(outCom, "%c\n", command);
                    //sizeRBT(rtree) ? displayRBT(rtree, stdout) : printf("EMPTY\n");
                    break;
                case 'r' :
                    fprintf(outCom, "%c\n", command);
                    //statisticsRBT(rtree, stdout);
                    break;
                case 'f' :
                    output = getString(commands);
                    if (output != 0) {
                        fprintf(outCom, "%c %s\n", command, output);
                        free(output);
                    }
                    break;
                default :
                    printf("SOMETHING WENT WRONG\n");
                    break;
            }
        }
        command = readChar(commands);
        if (command == EOF) break;
	}
    fclose(commands);
    fclose(outCom);
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