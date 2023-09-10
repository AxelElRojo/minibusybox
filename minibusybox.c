#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <stdbool.h>
#include <errno.h>

bool fileExists(const char* filename);
int touch(const char* filename);
int createDirectory(const char* filename);
int printFile(const char* filename);
int sleepSeconds(const char* time);

int main(int argc, char** argv){
	// strchr() returns the last appearance of a character
	// If the name contains a / it means the program's name starts after the last slash
	// If not, it means the program's name starts on argv[0][0] (i.e. executed from $PATH).
	char* command = strchr(argv[0], '/');
	if(command == NULL)
		command = argv[0];
	else
		command += 1;
	if(strcmp(command, "minibusybox") == 0)
		printf("Available commands:\n - touch\n - sleep\n - mkdir\n - cat\n");
	else if(argc == 2){
		if(strcmp(command, "touch") == 0)
			return touch(argv[1]);
		else if(strcmp(command, "sleep") == 0)
			return sleepSeconds(argv[1]);
		else if(strcmp(command, "mkdir") == 0)
			return createDirectory(argv[1]);
		else if(strcmp(command, "cat") == 0)
			return printFile(argv[1]);
		else
			printf("Unknown command\n");
	}else
		printf("Usage: %s <argument>\n", argv[0]);
	return 0;
}

bool fileExists(const char* filename){
	struct stat fileStat;
	return stat(filename, &fileStat) == 0;
}
int touch(const char* filename){
	FILE* fp;
	if(!fileExists(filename)){
		fp = fopen(filename, "w");
		if(fclose(fp) == EOF)
			return errno;
	}else
		if(utime(filename, NULL) == -1)
			return errno;
	return 0;
}
int createDirectory(const char* filename){
	if(mkdir(filename, 0755) == -1)
		switch(errno){
			case EACCES:
				printf("No write permissions!\n");
			break;
			case EDQUOT:
				printf("Block limit reached!\n");
			break;
			case EEXIST:
				printf("File already exists!\n");
			break;
			case EFAULT:
				printf("Pathname outside accessible range!\n");
			break;
			case EINVAL:
				printf("Directory's basename is invalid!\n");
			break;
			case ELOOP:
			case EMLINK:
				printf("Too many symlinks in pathname!\n");
			break;
			case ENAMETOOLONG:
				printf("Pathname is too long!\n");
			break;
			case ENOENT:
				printf("A pathname component doesn't exist!\n");
			break;
			case ENOMEM:
				printf("Kernel out of memory!\n");
			break;
			case ENOSPC:
				printf("Pathname has no room for the new directory!\n");
			break;
			case ENOTDIR:
				printf("A pathname component isn't a directory!\n");
			break;
			case EPERM:
				printf("The filesystem doesn't support directories!\n");
			break;
			case EROFS:
				printf("Pathname contains a readonly filesystem!\n");
			break;
			default:
				printf("Unknown error!\n");
		}else
			return 0;
		return errno;
}
int printFile(const char* filename){
	FILE* fp;
	fp = fopen(filename, "r");
	if(fp){
		char c = fgetc(fp);
		while(c != EOF){
			putchar(c);
			c = fgetc(fp);
		}
		fclose(fp);
		return 0;
	}else{
		printf("Failed to open file\n");
		return errno;
	}
}
int sleepSeconds(const char* time){
	long secs = atol(time);
	if(secs > 0 || time[0] == '0'){
		sleep(secs);
		return 0;
	}else{
		printf("Invalid value!\n");
		return 1;
	}
}