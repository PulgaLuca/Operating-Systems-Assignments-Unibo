/* file:  tennis.c */

/*
Ci sono 2 tennisti che si allenano stando entrambi in uno stesso lato del campo.
Una macchina sparapalle ad intervalli regolari lancia una palla da tennis
verso il lato del campo dove sono i due tennisti.
La palla viaggia molto lenta, dando tempo ad almeno uno dei due tennisti di colpirla.
Sentendo il rumore del lancio, ciascuno dei due tennisti si prepara a colpire la palla
ma la preparazione impiega un po' di tempo e quando infine cerca di colpire
la palla potrebbero succedere tre cose:
- la palla è stata colpita dall'altro tennista.
- la palla viene colpita dal tennista.
La palla colpita viene lanciata lontano e qui termina.
Il tennista che colpisce la palla esulta e attende il prossimo lancio.
Il tennista che arriva tardi impreca poi, sportivamente,
ammette la sconfitta e informa la macchina sparapalle di
sparare una nuova pallina e si mette in attesa del prossimo lancio.

Ci sono due tennisti e la macchina sparapalle (implementata nel main).
C'e' una variabile di stato StatoPalla che descrive la situazione della palla:
NONE la palla non e' ancora stata lanciata.
LANCIATA la palla e' stata lanciata ma non ancora colpita.
COLPITA la palla e' stata lanciata e colpita dal primo tennista
   ma ancora il secondo tennista non lo sa.
Quando il secondo tennista scopre che la palla e' stata gia' colpita
cambia lo stato della palla a NONE.

Attenzione: bisogna IMPEDIRE che il primo  tennista che colpisce la palla
possa colpire nuovamente la stessa palla se il secondo tennista
impiega parecchio tempo prima di accorgersi che la palla e' gia' stata colpita.

C'e' una mutex per proteggere variabili globali.
C'e' una condition variable condPuoiLanciare, su cui la macchina sparapalle
rimane in attesa che l'ultimo tennista abbia provato a colpire la palla
ed abbia messo a NONE lo stato della palla.
C'e' una condition variable condLanciato, su cui i tennisti rimangono in attesa
del lancio della palla.

Decidete voi se occorre aggiungere altre variabili.

La funzione attendi(secmin, secmax) serve ad attendere qualche secondo,
è una specie di sleep.

*/

#include "printerror.h"

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#include "DBGpthread.h"

#define NUMTENNISTI 2
#define MINATTESA 1
#define MAXATTESA 5

/* dati da proteggere */
pthread_mutex_t  mutex;
#define NONE 0
#define LANCIATA 1 
#define COLPITA 2
int StatoPalla=NONE; /* la situazione della palla */
pthread_cond_t condPuoiLanciare;
pthread_cond_t condLanciato;

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

	while( secrandom>0 ) {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 )
		{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	}
	return;
}

void *Tennista (void *arg) 
{ 
	char Tlabel[128];
	intptr_t indice;
	int IoColpita=0;

	indice=(intptr_t)arg;
	sprintf(Tlabel,"T%" PRIiPTR "",indice);

	/* VIC: DECIDETE VOI SE E' NECESSARIO METTERE QUI UNA LOCK */
	DBGpthread_mutex_lock(&mutex,Tlabel);

	while(1) {

		/* attendo lancio */
		/* VIC: DECIDETE VOI SE E' NECESSARIO METTERE QUI UNA LOCK */

		/* VIC: AGGIUNGERE DA QUI */
		while (StatoPalla==NONE || IoColpita==1 ) {
			IoColpita=0;
			printf("%s in attesa di lancio \n", Tlabel );
			fflush(stdout);
			DBGpthread_cond_wait(&condLanciato,&mutex,Tlabel);
		}
		/* VIC: AGGIUNGERE FINO A QUI */
		DBGpthread_mutex_unlock(&mutex,Tlabel);

		/* la palla e' stata lanciata, mi preparo a colpire */
		attendi(0,4);

		/* provo a colpire */
		DBGpthread_mutex_lock(&mutex,Tlabel);
		if (StatoPalla==LANCIATA ) {
			printf("%s ha colpito per primo \n", Tlabel );
			fflush(stdout);
			StatoPalla=COLPITA;

			/* VIC: AGGIUNGERE QUI SE NECESSARIO */
			IoColpita=1;


		} else if ( StatoPalla==COLPITA ) {
			printf("%s arrivato tardi, mannaggia \n", Tlabel );
			fflush(stdout);
			StatoPalla=NONE;

			/* VIC: AGGIUNGERE QUI SE NECESSARIO */
			IoColpita=0;

			/* avviso macchina sparapalle di fare altro lancio */
			DBGpthread_cond_broadcast(&condPuoiLanciare,Tlabel);

		}

		/* VIC: DECIDETE VOI SE E' NECESSARIO METTERE QUI UNA UNLOCK OPPURE NO */

	
		/* mi rimetto subito in attesa del prossimo lancio */
		printf("%s ricomincia \n", Tlabel );
		fflush(stdout);

	}
	pthread_exit(NULL); 
} 


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	intptr_t i;
	char Mlabel[128]="main";

	DBGpthread_mutex_init(&mutex, NULL, Mlabel); 
	DBGpthread_cond_init(&condPuoiLanciare, NULL, Mlabel);
	DBGpthread_cond_init(&condLanciato, NULL, Mlabel);
	StatoPalla=NONE;

	for(i=0;i<NUMTENNISTI;i++) {
		rc=pthread_create(&th,NULL,Tennista,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	sleep(2); /* aspetto che entrambi i tennisti siano pronti */


	/* cominciano i lanci */
	DBGpthread_mutex_lock(&mutex,Mlabel);
	while(1) {
		while( StatoPalla!=NONE ) {
			DBGpthread_cond_wait(&condPuoiLanciare,&mutex,Mlabel);
		}
		/* lancio palla */
		StatoPalla=LANCIATA;
		DBGpthread_cond_broadcast(&condLanciato,Mlabel);
		printf("%s lancia palla \n", Mlabel );
		fflush(stdout);

		/* mi rimetto in attesa che entrambi i tennisti abbiano finito */

	}

	pthread_exit(NULL);
	return(0); 
} 
  
