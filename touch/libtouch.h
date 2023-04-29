#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <utime.h>
#include <errno.h>
bool fileExists(const char* filename);
int touch(const char* filename);