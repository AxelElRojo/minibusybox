#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/libmkdir.h"

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
		if(strcmp(command, "mkdir") == 0)
			return createDirectory(argv[1]);
		else
			printf("Unknown command\n");
	}else
		printf("Usage: %s <argument>\n", argv[0]);
	return 0;
}