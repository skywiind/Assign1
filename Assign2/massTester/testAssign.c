#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TIME_LIMIT 10  
#define AND &&

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

int timeout = 0;
int child_done = 0;

void child_handler(int sig) {
    child_done = 1;
}

void alarm_handler(int sig) {
    timeout = 1;
}

int copyFile(char*, char*);

int main(int argc, char **argv) {
	
	char filename[100];
	char copyname[100];
	char command[100];
	char arguments[100];
	char extension[100];
	char ccfName[100];
	char arg1[10], arg2[100], arg3[100];
	
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
	int crashed = 0;
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
	//DIR* ignoreSub = opendir("./ignoreSub");
	//DIR* ignoreExp = opendir("./ignoreExp");
	DIR* extra = opendir("./extra");
	
	if (userCodeDir == NULL) {
		printf("Unable to open directory to user's code. Directory must exist and be within the program's folder.\n");
		return -1;
	}
	if (testDir == NULL) {
		printf("Unable to open directory to test base code. Directory must exist and be within the program's folder.\n");
		return -1;
	} 
	if (anwserDir == NULL) {
		printf("Unable to open directory to answers. Directory must exist and be within the program's folder.\n");
		return -1;
	}
	if (extra == NULL) {
		printf("Unable to open directory to corpus and commands. Directory must exist and be within the program's folder.\n");
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
	system("rm ./diffOut/*");
	system("rm ./results/*");
	if (reset) {
		sprintf(command, "cp -p ./ignoreSub/*.c ./submission/");
		system(command);
		sprintf(command, "cp -p ./ignoreSub/*.arguments ./submission/");
		system(command);
		sprintf(command, "cp -p ./ignoreExp/*.expected ./expected/");
		system(command);
		sprintf(command, "rm ./ignoreSub/*.c");
		system(command);
		sprintf(command, "rm ./ignoreSub/*.arguments");
		system(command);
		sprintf(command, "rm ./ignoreExp/*.expected");
		system(command);
		return 0;
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
	int hasArgs = 0;
	while ((de = readdir(testDir)) != NULL) {
		timeout = 0;
		child_done = 0;
		if (i > 1) system("rm ./working/assign");
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
		extension[0] = '\0';
		int period = 0;
		int extStart = 0;
		for (int i = 0; i < (int)strlen(de->d_name); ++i) {
			if (period == 1) extension[extStart++] = de->d_name[i];
			if (de->d_name[i] == '.') period = 1;
		}
		if (strncmp(extension, "arguments", 9) == 0) hasArgs = 1;
		else hasArgs = 0;
		
		if (hasArgs == 0) {
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
		}
		else if (hasArgs == 1) {
			char temp[100];
			strcpy(temp, de->d_name);
			char *fName;
			fName = strtok(temp, ".");
			
			strcpy(ccfName, fName);
			ccfName[strlen(ccfName) - 2] = '\0';
			
			strcpy(filename, "./extra/");
			strcat(filename, ccfName);
			strcat(filename, ".corpus");
			strcpy(copyname, "./working/");
			strcat(copyname, ccfName);
			strcat(copyname, ".corpus");
			copyFile(filename, copyname);
			
			strcpy(filename, "./extra/");
			strcat(filename, ccfName);
			strcat(filename, ".commands");
			strcpy(copyname, "./working/");
			strcat(copyname, ccfName);
			strcat(copyname, ".commands");
			copyFile(filename, copyname);
			
			strcpy(filename, "./submission/");
			strcat(filename, de->d_name);
			FILE *argFile = fopen(filename, "r");
			fgets(arguments, 100, argFile);
			arguments[strlen(arguments) - 1] = '\0';
			fclose(argFile);
			
			token = fName;
			//strcpy(token, fName);
			system("chmod 0777 ./working/*");
			
			sprintf(command, "make -C ./working/ ARG=%s", "trees");
			printf("-------------------------------\n");
			printf("TEST #%d...\n\n", i);
			printf("Testing %s with user's code.\n", fName);
		}
		
		err = system(command);
		if (err == 0) {
			printf("No error!\n");
		} else {
			printf("An error occurred!\n");
		}
		
		if (valgrind) {
			printf("Executing with valgrind...\n");
			if (hasArgs == 0)
				sprintf(command, "valgrind --leak-check=full --error-exitcode=1 ./working/assign > ./results/user-%s.txt", token);
			else if (hasArgs == 1) {
				sscanf(arguments, "%s %s %s", arg1, arg2, arg3);
				sprintf(command, "valgrind --leak-check=full --error-exitcode=1 ./working/assign %s ./working/%s ./working/%s > ./results/user-%s.txt", arg1, arg2, arg3, token);
			}
			err = system(command);
			if (err) {
				printf(RED "Memory was not managed properly.\n" RESET);
				leaks++;
			}
			else {
				printf(GREEN "No leaks possible!\n" RESET);
				if (ignore) {
					if (hasArgs == 0) {
						sprintf(command, "cp ./submission/%s.c ./ignoreSub/%s.c", token, token);
						system(command);
						sprintf(command, "rm ./submission/%s.c", token);
						system(command);
					}
					else if (hasArgs == 1) {
						sprintf(command, "cp ./submission/%s.arguments ./ignoreSub/%s.arguments", token, token);
						system(command);
						sprintf(command, "rm ./submission/%s.arguments", token);
						system(command);
					}
					sprintf(command, "cp ./expected/%s.expected ./ignoreExp/%s.expected", token, token);
					system(command);
					sprintf(command, "rm ./expected/%s.expected", token);
					system(command);
				}
				noLeaks++;
			}
		}
		else {
			printf("Executing...\n");
			//-------------TIMEOUT CODE-----------//
			pid_t pid = fork();
			if (pid == -1) {
				perror("fork failed");
				exit(1);
			} else if (pid == 0) {
				// child process
				char path[100];
				strcpy(path, "./results/user-");
				strcat(path, token);
				strcat(path, ".txt");
				int fd = open(path, O_WRONLY | O_CREAT);
				if (fd == -1) {
					printf("Unable to open file, terminating...\n");
					return 1;
				}
				dup2(fd, 1);
				char temp1[100], temp2[100], temp3[100];
				if (hasArgs == 1) {
					sscanf(arguments, "%s %s %s", arg1, arg2, arg3);
					strcpy(temp1, arg1);
					strcpy(temp2, "./working/");
					strcat(temp2, arg2);
					strcpy(temp3, "./working/");
					strcat(temp3, arg3);
				}
				if (hasArgs == 1) crashed = execl("./working/assign","assign", temp1, temp2, temp3, NULL);
				else if (hasArgs == 0) crashed = execl("./working/assign", "assign", NULL);
				perror("exec failed");
				_exit(1);
			}
			signal(SIGALRM, alarm_handler);
			signal(SIGCHLD, child_handler);

			alarm(TIME_LIMIT);
			pause();

			if (timeout) {
				printf(RED "Test timed out\n" RESET);
				int result = waitpid(pid, NULL, WNOHANG);
				if (result == 0) {
					printf(RED "Killing child\n" RESET);
					kill(pid, 9);
					wait(NULL);
				}
			} else if (child_done) {
				wait(NULL);
			}
			//------------END TIMEOUT CODE----------//
		}
		
		if (crashed == 0) {
			sprintf(command, "diff ./results/user-%s.txt ./expected/%s.expected > ./diffOut/%s.diff", token, token, token);
			err = system(command);
		}
		else err = 1;
		if (err == 0) {
			printf(GREEN "Your output matches exactly!\n" RESET);
			if (ignore) {
				if (hasArgs == 0) {
						sprintf(command, "cp ./submission/%s.c ./ignoreSub/%s.c", token, token);
						system(command);
						sprintf(command, "rm ./submission/%s.c", token);
						system(command);
					}
				else if (hasArgs == 1) {
					sprintf(command, "cp ./submission/%s.arguments ./ignoreSub/%s.arguments", token, token);
					system(command);
					sprintf(command, "rm ./submission/%s.arguments", token);
					system(command);
				}
				sprintf(command, "cp ./expected/%s.expected ./ignoreExp/%s.expected", token, token);
				system(command);
				sprintf(command, "rm ./expected/%s.expected", token);
				system(command);
			}
			success++;
		} else {
			crashed ? printf(RED "Program crashed, exited with code %d\n" RESET, crashed) : printf(RED "the test FAILED at this point\n" RESET);
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