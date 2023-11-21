#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

static double salva = 0.0;

double quadrato(double n)
{
	salva = pow(n, 2);
	return (salva);
}
