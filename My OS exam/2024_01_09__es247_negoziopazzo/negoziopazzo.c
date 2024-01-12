/* file:  negoziopazzo.c

I clienti di un negozio entrano e prendono un biglietto numerato
univoco e crescente. Il numero stabilisce l'ordine con cui possono
accedere al bancone e servirsi UNO ALLA VOLTA.

Il biglietto viene preso in mutua esclusione
da una variabile int64_t bigliettoGlob
mediante una variabile apposita mutex   mutexDistributoreBiglietti.
Il primo biglietto distribuito vale 0,
i successivi vengono incrementati di 1 alla volta.

La variabile globale condivisa bigliettoSulDisplay 
indica quale e' il numero del biglietto del
prossimo cliente che puo' andare al bancone a servirsi.
Una variabile mutex   mutexTurno
protegge l'accesso alla variabile globale bigliettoSulDisplay.

La variabile globale bigliettoSulDisplay 
viene incrementata dal cliente che ha finito di servirsi,
quando va via dal bancone,
INVOCANDO UNA APPOSITA FUNZIONE IncrementaCasuale().
NOTA BENE: La funzione IncrementaCausale deve essere invocata mentre si
possiede la mutua esclusione sulla variabile mutexTurno.
Attenzione, l'incremento può essere anche maggiore di uno,
quindi alcuni clienti in attesa di essere serviti
vengono saltati.
Addirittura puo' capitare che il valore di bigliettoSulDisplay
diventi piu' grande del valore di bigliettoGlob,
quindi puo' capitare che un cliente appena arrivato
prenda un biglietto che non gli consente di essere servito.

Quando i clienti si accorgono che il loro numero è stato saltato,
si arrabbiano, urlano e se ne vanno maledicendo il negozio.

Ciascun cliente, servito o no, dopo essere uscito fa un giro
e poi ritorna al negozio per rifornirsi nuovamente.

Ciascun cliente impiega un tempo casuale per servirsi al bancone
e un tempo casuale per fare il giretto prima di tornare al negozio.

Ci sono 6 clienti. 
Implementare il sistema cercando di far si che 
il cliente che viene SALTATO se ne accorga appena possibile.

*/

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t intptr_t */
#include <inttypes.h>	/* uint64_t  PRIiPTR */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 

#include "printerror.h"
#include "DBGpthread.h"

#define NUMCLIENTI 6

/* variabili da proteggere */
int64_t bigliettoGlob=0;
int64_t bigliettoSulDisplay=0;
/* variabili per la sincronizzazione */
pthread_mutex_t  mutexDistributoreBiglietti;
pthread_mutex_t  mutexTurno;
pthread_cond_t   condCambioTurno;

void attendi( int secmin, int secmax) {
	int secrandom=0;
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

/* la funzione IncrementaCasuale deve essere utilizzata 
   SOLO MENTRE SI  DETIENE LA MUTUA ESCLUSIONE, poiché al suo interno
   viene modificata la variabile globale bigliettoSulDisplay
*/
void IncrementaCasuale( void ) {
	int incremento=0;

	/* incremento da 1 a 6 */
	incremento = 1 + ( random()%6 );
        printf("incremento di %i\n", incremento);fflush(stdout);
	bigliettoSulDisplay += incremento;
}

void *cliente (void *arg) 
{ 
	char Clabel[128];
	intptr_t indice;
	int64_t biglietto;

	indice=(intptr_t)arg;
	sprintf(Clabel,"C%" PRIiPTR "" , indice);

	while(1) 
	{
		/* il cliente aspetta qualche sec e poi entra nel negozio */
		attendi(0,4);
	
		/* cliente prende il biglietto */
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutexDistributoreBiglietti,Clabel); 
		biglietto=bigliettoGlob;
		bigliettoGlob++;

		printf("il cliente %s ha preso il biglietto %ld \n", Clabel, biglietto ); 
		fflush(stdout);
	
		/* rilascio la mutua esclusione sul distributore */
		DBGpthread_mutex_unlock(&mutexDistributoreBiglietti,Clabel); 
	
		/* cliente controlla ripetutamente il biglietto sul Display
		   per vedere se e' il suo turno oppure no.
		*/
		
		/* VIC: MODIFICARE PRIMA PARTE A PARTIRE DA QUI 
		   SE CLIENTE SALTATO stampare a video il suo biglietto 
		   e farlo uscire dal negozio
		   per poi farlo rientrare e prendere nuovo biglietto
		*/
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutexTurno,Clabel); 
		while( bigliettoSulDisplay < biglietto ) 
		{
			DBGpthread_cond_wait( &condCambioTurno, &mutexTurno,Clabel); 
		}
		if( bigliettoSulDisplay > biglietto )  {
			/* cioe' CLIENTE SALTATO */
			printf("cliente %s SALTATO, ha biglietto %ld ma display %ld \n", Clabel, biglietto, bigliettoSulDisplay ); 
			fflush(stdout);
			DBGpthread_mutex_unlock(&mutexTurno,Clabel); 

			continue; /* rientro nel while dall'inizio */
		}

		/* notare che rilascio la mutua esclusione,
		   in modo che i clienti SALTATI possano accorgersene il prima possibile
		*/
		DBGpthread_mutex_unlock(&mutexTurno,Clabel); 

		/* VIC: MODIFICARE PRIMA PARTE FINO A QUI */

		/* il cliente si serve al bancone */
		printf("il cliente %s si serve: biglietto %ld  bigliettoSulDisplay %ld \n", Clabel, biglietto, bigliettoSulDisplay ); 
		fflush(stdout);
		/* il cliente impiega un tempo casuale per servirsi */
		attendi(1,3);
	
		/* VIC: MODIFICARE SECONDA PARTE A PARTIRE DA QUI */

		/* VIC: aggiungere */
		DBGpthread_mutex_unlock(&mutexTurno,Clabel); 


		/* il cliente ha finito, definisce chi e' prossimo di turno */
		IncrementaCasuale(); /* occorre detenere la mutua esclusione */

		/* VIC: aggiungere */
		/* il cliente risveglia i clienti bloccati in attesa del cambio turno */
		DBGpthread_cond_broadcast( &condCambioTurno, Clabel ); 

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutexTurno,Clabel); 

		/* VIC: MODIFICARE SECONDA PARTE FINO A QUI */

		/* e il cliente se ne va */
		printf("il cliente %s se ne va \n", Clabel ); 
		fflush(stdout);
	}

	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	char label[128]="main";
	pthread_t   th; 
	int  rc;
	intptr_t i;

	srandom( time(NULL) );

	DBGpthread_mutex_init( &mutexDistributoreBiglietti, NULL, label); 
	DBGpthread_mutex_init( &mutexTurno, NULL, label); 
	DBGpthread_cond_init( &condCambioTurno, NULL, label); 

	bigliettoGlob=0;
	bigliettoSulDisplay=0;
	
	/* lancio i clienti */
	for(i=0;i<NUMCLIENTI;i++) {
		rc=pthread_create( &th, NULL,cliente,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
} 
  
  
  
