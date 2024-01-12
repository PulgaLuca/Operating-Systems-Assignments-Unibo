#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "dimezza.h"
#include "quadrato.h"

static double salva=0.0;

int main(void){
	salva=quadrato(dimezza(13.17));
	printf("%f\n", salva);
	return 0;
}
