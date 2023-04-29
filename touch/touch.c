#include "libtouch.h"
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