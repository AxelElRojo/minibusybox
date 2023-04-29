#include "libsleep.h"
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