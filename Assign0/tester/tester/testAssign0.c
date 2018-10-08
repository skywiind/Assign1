#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define AND &&

int copyFile(char*, char*);

int main() {
	
	char filename[100];
	char copyname[100];
	char command[100];
	char* token;
	int i = 0;
	int err;
	int success = 0;
	int failed = 0;
	
	struct dirent* de;
	
	DIR* userCodeDir = opendir("./assign0");
	DIR* testDir = opendir("./submission0");
	DIR* anwserDir = opendir("./expected0");
	DIR* workingDir = opendir("./working");
	DIR* resultsDir = opendir("./results");
	
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
	
	while (workingDir == NULL AND i < 10) {
		mkdir("working", 0777);
		workingDir = opendir("./working");
		i++;
	}
	
	i = 0;
	while (resultsDir == NULL AND i < 10) {
		mkdir("results", 0777);
		workingDir = opendir("./results");
		i++;
	}
	
	if (i == 10) {
		printf("Unable to create and/or open working directory.\n");
		return -2;
	}
	
	while ((de = readdir(userCodeDir)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
		strcpy(filename, "./assign0/");
		strcat(filename, de->d_name);
		strcpy(copyname, "./working/");
		strcat(copyname, de->d_name);
		copyFile(filename, copyname);
	}
	
	system("chmod 0777 ./working/*");
	
	i = 1;
	while ((de = readdir(testDir)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
		strcpy(filename, "./submission0/");
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
			printf("An error occured!\n");
		}
		
		printf("Executing...\n");
		sprintf(command, "./working/assign0 > ./results/user-%s.txt", token);
		system(command);
		
		sprintf(command, "diff ./results/user-%s.txt ./expected0/%s.txt", token, token);
		err = system(command);
		if (err == 0) {
			printf("Your output matches exactly!\n");
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
	
	if (failed != 0) {
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