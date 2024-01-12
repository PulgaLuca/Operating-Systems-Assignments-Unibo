#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

static double salva=0.0;

double dimezza( double a )
{
	salva=cos(a)/2.0;
	return salva;
}
