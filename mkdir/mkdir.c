#include "libmkdir.h"
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