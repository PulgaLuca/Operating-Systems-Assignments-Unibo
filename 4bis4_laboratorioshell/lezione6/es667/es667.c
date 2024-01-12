/*Esercizio667: implementare macro che deve stampare il prodotto dei due
valori interi passati come argomento
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define STAMPAPRODOTTO(X, Y) printf("%i\n",(X)*(Y))

int main(void) {
	STAMPAPRODOTTO(3, 2); /* stampa 6 */
	STAMPAPRODOTTO(3+5, 2); /* stampa 16 */
	return(0);
}
/*
Compilare e linkare il codice usando i seguenti comandi:
gcc -c -ansi -Wpedantic -Wall es667.c
gcc -o prodotto.exe es667.o
*/
