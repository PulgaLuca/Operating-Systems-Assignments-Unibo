#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

static double salva = 0.0;

double dimezza(double n)
{
	salva = cos(n)/2.0;
	return (salva);
}
