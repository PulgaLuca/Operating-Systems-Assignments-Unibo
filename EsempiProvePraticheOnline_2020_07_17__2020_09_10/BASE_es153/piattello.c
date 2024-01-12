/* file:  piattello.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMTIRATORI 10
#define DELAYTRADUEPIATTELLI8sec 8

/* dati da proteggere */
int PiattelloInVolo=0;  /* occorre sapere se un piattello e' in volo */
int PiattelloColpito=0; /* conta quanti tiratori hanno colpito il piattello */

/* variabili per la sincronizzazione - AGGIUNGETE QUELLO CHE VI SERVE */
pthread_mutex_t  mutex;
pthread_cond_t   condSvegliaTiratori;


void attendi( int min, int max) {
	int secrandom=0;
	if( min > max ) return;
	else if ( min == max ) 
		secrandom = min;
	else
		secrandom = min + ( random()%(max-min+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 ) 
			{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
	return;
}

void *Tiratore (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Tiratore%" PRIiPTR "",indice);

  /* notare che faccio la lock fuori dal loop */
  DBGpthread_mutex_lock(&mutex,Plabel);

	while ( 1 ) {

		/* il tiratore  attende l'inizio del volo del piattello */
		printf("tiratore %s attende piattello \n", Plabel);
		fflush(stdout);

		/* VIC: da completare  */
		DBGpthread_cond_wait(&condSvegliaTiratori,&mutex,Plabel);
		/* VIC: FINE AGGIUNTA */

		printf("tiratore %s mira e .... \n", Plabel);
		fflush(stdout);

		/*  VIC: da completare  */
		DBGpthread_mutex_unlock(&mutex,Plabel);
		/* VIC: FINE AGGIUNTA */

		/* il tiratore si prepara a sparare impiegando da 2 a 4 secondi */
		/* NEL FRATTEMPO IL PIATTELLO DEVE POTER VOLARE */
		attendi( 2, 4 );


		/* VIC: da completare - attenzione, il piattello potrebbe essere gia' caduto. */
  	DBGpthread_mutex_lock(&mutex,Plabel);
		/* VIC: FINE AGGIUNTA */

    if( PiattelloInVolo==1 ) {
      printf("tiratore %s spara e colpisce. Aaaaaaleeee\n", Plabel);
      PiattelloColpito++; /* non richiesto, conta quanti hanno colpito il piattello */
    }
    else
      printf("tiratore %s arrivato tardi, vaffa\n", Plabel);

		/* il tiratore finisce il tentativo di sparare al piattello in volo */
    fflush(stdout);

    /* NOTARE CHE qui NON FACCIO LA unlock, COSI' SONO SICURO CHE
       il tiratore si mettera' in wait senza che un nuovo piattello
       abbia potuto cambiare la propria condizione mettendosi in volo.
			 Non sarebbe necessario perche' il main aspetta molto prima di
			 creare un nuovo piattello.
     */

	}
	pthread_exit(NULL); 
}


void *Piattello (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Piattello%" PRIiPTR "",indice);

	/*  ipotizziamo che il precedente piattello sia gia' caduto
	    e che quindi piattello_in_volo ora qui valga ZERO.  */

  DBGpthread_mutex_lock(&mutex,Plabel);
	printf("piattelo %s inizia volo\n", Plabel);
	fflush(stdout);
  PiattelloInVolo=1;	/* il piattello inizia il volo */
  PiattelloColpito=0; /* serve per contare quanti hanno colpito il piattello */

	/* VIC: da completare - come fanno i tiratori a sapere che il piattello ora vola? */
	DBGpthread_cond_broadcast(&condSvegliaTiratori,Plabel);
  DBGpthread_mutex_unlock(&mutex,Plabel);
	/* VIC: FINE AGGIUNTA */


	/* il piattello vola per tre secondi -
		DURANTE STO PERIODO I TIRATORI che si svegliano possono sparare.
		Quindi ho dovuto rilasciare la mutua esclusione. */

	attendi( 3, 3 );


	/*  VIC: da completare - il piattello controlla se e' stato colpito */
	DBGpthread_mutex_lock(&mutex,Plabel);
	/* VIC: FINE AGGIUNTA */

	
  PiattelloInVolo=0;
  if( PiattelloColpito>0 ) {
    printf("piattelo %s COLPITO cade a terra\n", Plabel);
  } else {
    printf("piattelo %s NON COLPITO atterra\n", Plabel);
  }
	fflush(stdout);
  PiattelloColpito=0; /* il prossimo piattello partira' intatto */
  DBGpthread_mutex_unlock(&mutex,Plabel);

	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	uintptr_t i=0;
	int seme;

	seme=time(NULL);
	srandom(seme);

  rc = pthread_mutex_init(&mutex, NULL);
  if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	/* VIC: INIZIALIZZATE VOSTRE VARIABILI CONDIVISE e tutto quel che serve - fate voi */
  rc = pthread_cond_init(&condSvegliaTiratori, NULL);
  if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	/* VIC: FINE AGGIUNTA */

	/* all'inizio non c'e' nessun piattello in volo */
  PiattelloInVolo=0;
	PiattelloColpito=0;

	/* CREAZIONE PTHREAD dei tiratori */
	for(i=0;i<NUMTIRATORI;i++) {
		rc=pthread_create(&th,NULL,Tiratore,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* CREAZIONE NUOVO PIATTELLO OGNI 8 secondi */
	i=0;
	while(1) {
			/* un nuovo piattello ogni 8 secondi */
			attendi( DELAYTRADUEPIATTELLI8sec, DELAYTRADUEPIATTELLI8sec );
			i++;

			/* crea pthread piattello */
			rc=pthread_create(&th,NULL,Piattello,(void*)i);
 			if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL);
	return(0); 
} 
  
