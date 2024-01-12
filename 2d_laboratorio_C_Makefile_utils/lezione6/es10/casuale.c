#ifndef _POSIX_SOURCE
#define	_POSIX_SOURCE
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(void){
	int counter=0;
	srand(time(NULL));
	while(1){
		counter++;
		if(rand()%10==1){
			break;
		}
	}
	printf("%i:\n", counter);
	fflush(stdout);
	return 0;
}

