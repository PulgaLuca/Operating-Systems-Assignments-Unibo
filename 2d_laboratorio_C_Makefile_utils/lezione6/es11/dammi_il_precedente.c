#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

unsigned int dammi_il_precedente(unsigned int a){
	static unsigned int prec=0;
	unsigned int temp;
	printf("Prec: %u, Act: %u", prec, a);
	temp=prec;
	prec=a;
	return temp;
}

int main(void){
	srand(time(NULL));
	while(1){
		int a = dammi_il_precedente(rand());
		if(a%10==3){
			break;
		}
	}
	return 0;
}
