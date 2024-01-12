/* file: striscepedonali.c 

In una strada a senso unico c'e' un attraversamento pedonale.
Solo una auto alla volta può passare sulle striscie pedonali
e impiega 2 secondi.
Le auto devono dare la precedenza ai pedoni che stanno attraversando
ed anche ai pedoni che sono ai bordi e sono in attesa di attraversare.
Ciascun pedone impiega 3 secondi per attraversare la strada.
Mentre un pedone attraversa sulle striscie anche gli altri pedoni
possono attraversare.
Le auto possono passare se sono vere le seguenti tre condizioni:
- nessun pedone sta attraversando
- nessun pedone e' in attesa di attraversare
- nessuna auto sta passando.
Invece, un pedone può attraversare se nessuna auto sta passando in quel momento sulle striscie pedonali.

Ogni auto, dopo essere passata sulle striscie pedonali,
fa un giro in citta' e poi cerca nuovamente di attraversare.
Ogni pedone, dopo avere attraversato la strada, fa un giretto
e poi cerca nuovamente di attraversare.


Ci sono 4 variabili intere:
numPedoniAttraversano	i pedoni che stanno attraversando
numPedoniInAttesa 	 i pedoni che vorrebero attraversare
autoPassa		un auto sta passando (vale 0 o 1 )
numAutoInAttesa		num auto che vorrebbero transitare

Ci sono inoltre una mutex per proteggere i dati condivisi
e due condition variable, una per le auto ed una per i pedoni.

La funzione attendi(secmin, secmax) serve ad attendere un numero casuale
di secondi, compresi tra secmin e secmax,
è una specie di sleep.

*/ 

#include "printerror.h"

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* intptr_t */
#include <inttypes.h>	/* format per stampa intptr_t ad esempio PRIiPTR */
#include <pthread.h> 

#include "DBGpthread.h"

#define NUMPEDONI 4
#define NUMAUTO 2

/* Buffer da proteggere */

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t condPedoni, condAuto;
int numPedoniAttraversano=0, numPedoniInAttesa=0, autoPassa=0, numAutoInAttesa=0;

void attendi( int secmin, int secmax) {
        int secrandom=0;
        static int inizializzato=0;
        if( inizializzato==0 ) {
                srandom( time(NULL) );
                inizializzato=1;
        }
        if( secmin > secmax ) {
                printf("attendi: parametri errati: secmin %i secmax %i"
                        " - TERMINO PROCESSO\n", secmin, secmax ),
                exit(1);
        }
        else if ( secmin == secmax )
                secrandom = secmin;
        else
                secrandom = secmin + ( random()%(secmax-secmin+1) );
        do {
                /* printf("attendi %i\n", secrandom);fflush(stdout); */
                secrandom=sleep(secrandom);
                if( secrandom>0 )
                { printf("sleep interrupted - continue\n"); fflush(stdout); }
        } while( secrandom>0 );
return;
}


void *Auto (void *arg) 
{ 
	char Alabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Alabel,"A%" PRIiPTR "", indice);

	while(1) {
		/* L'auto vuole attraversare, 
		   per prima cosa dichiara di voler attraversare */
		DBGpthread_mutex_lock(&mutex,Alabel); 
		numAutoInAttesa++;
		printf("Auto %s in attesa di attraversare \n", Alabel ); 
		fflush(stdout);
		
		/* L'auto vuole attraversare, ma lo puo' fare se e solo se
		sono vere le seguenti tre condizioni:
			nessun pedone sta attraversando
			nessun pedone e' in attesa di attraversare
			nessuna auto sta attraversando.
		In caso contrario aspetta.
		*/

		/* VIC - VERIFICARE E CORREGGERE IL CODICE A PARTIRE DA QUI */
		while	(
    				autoPassa!=0 ||
				numPedoniAttraversano!=0 ||
				numPedoniInAttesa!=0
			)
			DBGpthread_cond_wait(&condAuto,&mutex,Alabel); 

		/* VIC - VERIFICARE E CORREGGERE IL CODICE FINO A QUI */


		numAutoInAttesa--;
    		autoPassa++;
		printf("Auto %s attraversa \n", Alabel ); 
		fflush(stdout);
		DBGpthread_mutex_unlock(&mutex,Alabel); 

		sleep( 2 );  /* auto attraversa */
		
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutex,Alabel); 
    		autoPassa--;
		printf("Auto %s finisce di attraversare \n", Alabel ); 
		fflush(stdout);

		/* se ci sono pedoni in attesa di attraversare li risveglia,
		   ALTRIMENTI se ci sono auto in attesa le risveglia,
		   altrimenti non fa niente.
		*/
		if( numPedoniInAttesa > 0 ) 
			DBGpthread_cond_broadcast(&condPedoni,Alabel); 
		else if( numAutoInAttesa > 0 ) 
			DBGpthread_cond_signal(&condAuto,Alabel); 
		DBGpthread_mutex_unlock(&mutex,Alabel); 

		/* l'auto fa un giretto e poi torna alle striscie pedonali */
		attendi(2,3);  /* aspetta un tempo tra 2 e 3 secondi */
	}
	pthread_exit(NULL); 
} 

void *Pedone (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"P%" PRIiPTR "", indice);

	while(1) {
		/* il pedone vuole attraversare, 
		   per prima cosa dichiara di voler attraversare */
		DBGpthread_mutex_lock(&mutex,Plabel); 
		numPedoniInAttesa++;
		printf("Pedoni %s in attesa di attraversare \n", Plabel ); 
		fflush(stdout);
		
		/* Il pedone vuole attraversare, ma lo puo' fare se e solo se
			nessuna auto sta attraversando.
		In caso contrario aspetta.
		*/

		while	( autoPassa!=0 ) 
			DBGpthread_cond_wait(&condPedoni,&mutex,Plabel); 

		numPedoniInAttesa--;
    		numPedoniAttraversano++;
		/* se ci sono altri pedoni in attesa di attraversare,
		   allora questo pedone li risveglia tutti */
		if( numPedoniInAttesa > 0 ) 
			DBGpthread_cond_broadcast(&condPedoni,Plabel); 

		printf("pedone %s attraversa \n", Plabel ); 
		fflush(stdout);
		DBGpthread_mutex_unlock(&mutex,Plabel); 

		sleep( 2 );  /* pedone attraversa */
		
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutex,Plabel); 
    		numPedoniAttraversano--;
		printf("pedone %s finisce di attraversare \n", Plabel ); 
		fflush(stdout);

		/* Se ci sono pedoni in attesa di attraversare li risveglia,
		   ALTRIMENTI
		   se nessun pedone sta attraversando E nessun pedone e' in attesa
		   E ci sono auto in attesa allora risveglia un auto.
		*/

		if( numPedoniInAttesa > 0 ) 
			DBGpthread_cond_broadcast(&condPedoni,Plabel); 
		else if(
			numPedoniAttraversano==0 &&
			numPedoniInAttesa==0 &&
			numAutoInAttesa > 0 
			) 
			DBGpthread_cond_signal(&condAuto,Plabel); 

		DBGpthread_mutex_unlock(&mutex,Plabel); 

		/* il pedone fa un giretto e poi torna alle striscie pedonali */
		attendi(4,6);  /* aspetta un tempo tra 4 e 6 secondi */

	}
	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	intptr_t i;

	DBGpthread_mutex_init(&mutex, NULL, "main"); 
	DBGpthread_cond_init(&condAuto, NULL, "main"); 
	DBGpthread_cond_init(&condPedoni, NULL, "main"); 

	for(i=0;i<NUMAUTO;i++) {
		rc=pthread_create( &th,NULL,Auto,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	for(i=0;i<NUMPEDONI;i++) {
		rc=pthread_create( &th,NULL,Pedone,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 
	return(0); 
} 
  
  
  
