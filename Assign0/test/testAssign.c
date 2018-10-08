#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define AND &&

int copyFile(char*, char*);

int main(int argc, char **argv) {
	
	char filename[100];
	char copyname[100];
	char command[100];
	char* token;
	int i = 0, j = 0;
	int err;
	int success = 0;
	int failed = 0;
	int leaks = 0;
	int noLeaks = 0;
	int valgrind = 0;
	int reset = 0;
	int ignore = 0;
	
	struct dirent* de;
	
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "-valgrind") == 0) valgrind = 1;
		if (strcmp(argv[i], "-reset") == 0) reset = 1;
		if (strcmp(argv[i], "-ignore") == 0) ignore = 1;
	}
	
	DIR* userCodeDir = opendir("./assign");
	DIR* testDir = opendir("./submission");
	DIR* anwserDir = opendir("./expected");
	DIR* workingDir = opendir("./working");
	DIR* resultsDir = opendir("./results");
	DIR* ignoreSub = opendir("./ignoreSub");
	DIR* ignoreExp = opendir("./ignoreExp");
	
	if (userCodeDir == NULL) {
		printf("Unable to open directory to user's code. Directory must exist and be within the program's folder.\n");
		return -1;
	} else if (testDir == NULL) {
		printf("Unable to open directory to test base code. Directory must exist and be within the program's folder.\n");
		return -1;
	} else if (anwserDir == NULL) {
		printf("Unable to open directory to answers. Directory must exist and be within the program's folder.\n");
		return -1;
	}
	//Add errors for not opening ignore directories 
	while (workingDir == NULL AND i < 10) {
		mkdir("working", 0777);
		workingDir = opendir("./working");
		i++;
	}
	
	i = 0;
	while (resultsDir == NULL AND j < 10) {
		mkdir("results", 0777);
		workingDir = opendir("./results");
		j++;
	}
	
	if (i == 10 || j == 10) {
		printf("Unable to create and/or open working directory or results directory.\n");
		return -2;
	}
	if (reset) {
		sprintf(command, "cp ./ignoreSub/*.c ./submission/");
		system(command);
		sprintf(command, "cp ./ignoreExp/*.txt ./expected/");
		system(command);
		sprintf(command, "rm ./ignoreSub/*.c");
		system(command);
		sprintf(command, "rm ./ignoreExp/*.txt");
		system(command);
	}
	while ((de = readdir(userCodeDir)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
		strcpy(filename, "./assign/");
		strcat(filename, de->d_name);
		strcpy(copyname, "./working/");
		strcat(copyname, de->d_name);
		copyFile(filename, copyname);
	}
	
	system("chmod 0777 ./working/*");
	
	i = 1;
	while ((de = readdir(testDir)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
		strcpy(filename, "./submission/");
		strcat(filename, de->d_name);
		strcpy(copyname, "./working/");
		strcat(copyname, de->d_name);
		copyFile(filename, copyname);
		token = strtok(de->d_name, ".");
		
		system("chmod 0777 ./working/*");
		
		sprintf(command, "make -C ./working/ ARG=%s", token);
		printf("-------------------------------\n");
		printf("TEST #%d...\n\n", i);
		printf("Compiling %s with user's code.\n", de->d_name);
		
		err = system(command);
		if (err == 0) {
			printf("No error!\n");
		} else {
			printf("An error occurred!\n");
		}
		
		if (valgrind) {
			printf("Executing with valgrind...\n");
			sprintf(command, "valgrind ./working/assign --error-exitcode=5 > ./results/user-%s.txt", token);
			err = system(command);
			if (err == 0) {
				printf("No leaks possible!\n");
				if (ignore) {
					char sub[100], exp[100];
					strcpy(sub, token);
					strcpy(exp, token);
					strcat(sub, ".c");
					strcat(exp, ".txt");
					sprintf(command, "cp ./submission/%s.c ./ignoreSub/%s.c", token, token);
					system(command);
					sprintf(command, "rm ./submission/%s.c", token);
					system(command);
					sprintf(command, "cp ./expected/%s.txt ./ignoreExp/%s.txt", token, token);
					system(command);
					sprintf(command, "rm ./expected/%s.txt", token);
					system(command);
				}
			}
			else {
				printf("Memory was not managed properly.\n");
				leaks++;
			}
			noLeaks++;
		}
		else {
			printf("Executing...\n");
			sprintf(command, "./working/assign > ./results/user-%s.txt", token);
			system(command);
		}
		sprintf(command, "diff ./results/user-%s.txt ./expected/%s.txt", token, token);
		err = system(command);
		if (err == 0) {
			printf("Your output matches exactly!\n");
			if (ignore) {
				char sub[100], exp[100];
				strcpy(sub, token);
				strcpy(exp, token);
				strcat(sub, ".c");
				strcat(exp, ".txt");
				sprintf(command, "cp ./submission/%s.c ./ignoreSub/%s.c", token, token);
				system(command);
				sprintf(command, "rm ./submission/%s.c", token);
				system(command);
				sprintf(command, "cp ./expected/%s.txt ./ignoreExp/%s.txt", token, token);
				system(command);
				sprintf(command, "rm ./expected/%s.txt", token);
				system(command);
			}
			success++;
		} else {
			printf("the test FAILED at this point\n");
			failed++;
		}
		printf("-------------------------------\n");
		i++;
	}
	
	printf("TEST COMPLETE\n\n");
	
	printf("Tests passed: %d\n", success);
	printf("Test failed: %d\n", failed);
	if (valgrind) {
		printf("Number of tests with memory leaks: %d\n", leaks);
		printf("Number of tests with proper memory management: %d\n", noLeaks);
	}
	
	if (failed != 0 || (valgrind AND leaks != 0)) {
		printf("There are test failures, you need to resubmit.\n");
	} else {
		printf("All tests passed!\n");
	}
}

int copyFile(char* src, char* dest) {
	FILE* fpSrc = fopen(src, "r");
	FILE* fpDest = fopen(dest, "w");
	unsigned char* buffer;
	unsigned long length;
	
	if (fpSrc == NULL) {
		printf("Unable to open %s, terminating...\n", src);
		exit(-2);
	} else if (fpDest == NULL) {
		printf("Unable to open %s, terminating...\n", dest);
		exit(-2);
	}
	
	fseek(fpSrc, 0, SEEK_END);
	length = ftell(fpSrc);
	fseek(fpSrc, 0, SEEK_SET);
	
	buffer = malloc(sizeof(char) * length+1);
	if (!buffer) {
		fprintf(stderr, "Memory error.\n");
		exit(-3);
	}
	
	fread(buffer, length, 1, fpSrc);
	fwrite(buffer, length, 1, fpDest);
	fclose(fpSrc);
	fclose(fpDest);
	
	return 1;
}