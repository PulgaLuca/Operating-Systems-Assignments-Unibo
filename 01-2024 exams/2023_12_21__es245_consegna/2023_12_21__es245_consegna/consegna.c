/* consegna.c 

in un magazzino arrivano continuamente dei Corrieri
che devono consegnare ciascuno una scatola di cristalli fragili
ad un unico magazziniere.

La consegna deve essere fatta secondo un certo protocollo
per impedire che la scatola cada per terra e rompa i cristalli.

Quando un corriere arriva in magazzino, se il magazziniere
NON E' PRONTO a ricevere la scatola, allora il corriere aspetta
(potrebbero esserci piu corrieri in attesa).

Quando il magazziniere e' pronto, dice di essere pronto,
sveglia uno dei corrieri in fila
e si mette in attesa di ricevere la scatola protendendo le braccia.

Il corriere svegliato (oppure un corriere che
 e' arrivato ed ha visto il magazziniere pronto),
- appoggia la scatola sulle braccia del magazziniere,
- poi avvisa il magazziniere di avere depositato la scatola sulle sue braccia,
- poi aspetta che il magazziniere gli dica di andarsene,
infine se ne va.
Fatta la consegna, il corriere va a prendere una altra scatola 
da consegnare successivamente, e cosi' all'infinito.

Quando il magazziniere viene avvisato di avere una scatola in braccio,
- dice al corriere di andarsene, poi va a depositare
la scatola in uno scaffale di dimensione infinita
e poi torna a vedere se ci sono altri corrieri,
e cosi' via all'infinito.

Ci sono alcune variabili intere:
int numCorrieriInAttesa
int magazziniereProntoARicevere  vale 0 o 1

una mutex ed alcune condition variable:
condCodaCorrieri
condMagazziniereAspettaScatola
DECIDETE VOI SE SERVONO ALTRE condition variable.

Completare il codice.

*/

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMCORRIERI 3

int numCorrieriInAttesa=0;
int magazziniereProntoARicevere=0;

pthread_mutex_t mutex;
pthread_cond_t condMagazziniereAspettaScatola;
pthread_cond_t condCodaCorrieri;

void *Corriere(void *arg) {
	char Clabel[128]; 
	intptr_t index=(intptr_t)arg;

	sprintf( Clabel, "C%" PRIiPTR "", index);

	while(1) {
		/* corriere vede se il magazziniere e' pronto,
		   altrimenti si mette in coda
		*/

		printf("%s vuole consegnare\n",Clabel);
		fflush(stdout);

		DBGpthread_mutex_lock(&mutex, Clabel);
		numCorrieriInAttesa++;
		while( magazziniereProntoARicevere==0 ) {
			DBGpthread_cond_wait(&condCodaCorrieri,&mutex, Clabel);
		}
		numCorrieriInAttesa--;

		/* consegno scatola */

		/* ho appoggiato scatola sulle braccia del magazziniere */

		/* VIC: COMPLETARE PRIMA PARTE A PARTIRE DA QUI */

		magazziniereProntoARicevere=0;
		/* sveglio il magazziniere */
		DBGpthread_cond_signal(&condMagazziniereAspettaScatola, Clabel);
		/* aspetto che il magazziniere mi dica di andarmene */
		DBGpthread_cond_wait(&condMagazziniereAspettaScatola,&mutex, Clabel);

		/* VIC: COMPLETARE SECONDA PARTE FINO A QUI */
		printf("%s ha consegnato\n",Clabel);
		fflush(stdout);
		DBGpthread_mutex_unlock(&mutex, Clabel);

		sleep(1);
	}
	pthread_exit(NULL); 
}

void *Magazziniere(void *arg) {

	char Mlabel[128]="M"; 

	while(1) {
		DBGpthread_mutex_lock(&mutex, Mlabel);

	 	/* magazziniere e' pronto a ricevere */
		magazziniereProntoARicevere=1;
	 	/* magazziniere sveglia qualcuno in coda da cui ricevere scatola */
		DBGpthread_cond_signal(&condCodaCorrieri, Mlabel);

	 	/* magazziniere aspetta scatola */
		DBGpthread_cond_wait(&condMagazziniereAspettaScatola,&mutex, Mlabel);
		printf("%s riceve scatola\n",Mlabel);
		fflush(stdout);

		/* VIC: COMPLETARE SECONDA PARTE A PARTIRE DA QUI */
	 	/* magazziniere ha ricevuto scatola, dice a corriere di andarsene */
		
		DBGpthread_cond_signal(&condMagazziniereAspettaScatola, Mlabel);

		/* VIC: COMPLETARE SECONDA PARTE FINO A QUI */
		DBGpthread_mutex_unlock(&mutex, Mlabel);

		printf("%s deposita scatola in magazzino\n",Mlabel);
		fflush(stdout);

		sleep(3);

	}
	pthread_exit(NULL); 
}

int main(){
	int rc;  intptr_t i;
	pthread_t tId;
	
	DBGpthread_cond_init(&condMagazziniereAspettaScatola, NULL,"main");
	DBGpthread_cond_init(&condCodaCorrieri, NULL, "main");
	DBGpthread_mutex_init(&mutex, NULL, "main"); 

	/* VIC: aggiungere eventuali vostre inizializzazioni */
	

	
	/*creo i thread */
	rc=pthread_create( &tId, NULL, Magazziniere, NULL ); 
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");

	for(i=0;i<NUMCORRIERI;i++) {
		rc=pthread_create( &tId, NULL, Corriere, (void*)i ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 
	return 0;
}
