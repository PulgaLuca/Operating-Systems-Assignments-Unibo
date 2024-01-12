/* staffettasemplice_ConTurno.c */

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "DBGpthread.h"


#define NUM_ALFA 5
#define NUM_BETA 4

pthread_mutex_t mutex;
pthread_cond_t cond_alfa; /* qui attendono gli alfa */
pthread_cond_t cond_beta; /* qui attendono i beta */

/*per indicare il turno dei corridori alfa*/
int turno_tra_alfa=0;
/*pre indicare il turno dei corridori beta*/
int turno_tra_beta=0;

#define TURNOALFA 0
#define TURNOBETA 1

/* indica quale gruppo di corridori e' di turno, parte per primo un ALFA */
int turno_gruppo = TURNOALFA;  



void *alfa(void *arg){
	char Alabel[128]; 
	char Alabelsignal[128]; 
	int index=*((int*)arg);
	/* NOTA BENE: USERO' IL MIO INDICE come mio turno tra gli alfa */

 	free(arg);

	sprintf( Alabel, "A%d", index);
	sprintf( Alabelsignal, "A%d->B", index);

	while(1){
		/* COMPLETARE */
		/* attendo il mio turno */
		DBGpthread_mutex_lock(&mutex, Alabel);
		while (turno_tra_alfa != index || turno_gruppo!=TURNOALFA){
			DBGpthread_cond_wait(&cond_alfa, &mutex, Alabel);
		}
		/* parto per il mio giro */
		printf("alfa %d parte\n",index);
		sleep(1);
		printf("alfa %d ha completato il giro\n",index);
		
		/* COMPLETARE */
		/* stabilisco chi e' il successivo corridore alfa */
		if(turno_tra_alfa==NUM_ALFA-1){
			turno_tra_alfa=0;
		}
		else{
			turno_tra_alfa++;
		}	
		/* COMPLETARE */
		/* il prossimo corridore deve essere un beta */
		turno_gruppo=TURNOBETA;
		/* COMPLETARE */
		/* sveglio i beta */	
		DBGpthread_cond_broadcast(&cond_beta, Alabel);
		DBGpthread_mutex_unlock(&mutex, Alabel);
	}
	pthread_exit(NULL); 
}


void *beta(void *arg){
	char Blabel[128]; 
	char Blabelsignal[128]; 
	int index=*((int*)arg);
	/* NOTA BENE: USERO' IL MIO INDICE come mio turno tra i beta */

 	free(arg);

	sprintf( Blabel, "B%d", index);
	sprintf( Blabelsignal, "B%d->A", index);

	while(1){
		/* COMPLETARE */
		/* attendo il mio turno */
		DBGpthread_mutex_lock(&mutex, Blabel);
		while (turno_tra_beta != index || turno_gruppo!=TURNOBETA){
			DBGpthread_cond_wait(&cond_beta, &mutex, Blabel);
		}
		/* parto per il mio giro */
		printf("beta %d parte\n",index);
		sleep(1);
		printf("beta %d ha completato il giro\n",index);
		
		/* COMPLETARE */
		/* stabilisco chi e' il successivo corridore beta */
		if(turno_tra_beta==NUM_BETA-1){
			turno_tra_beta=0;
		}
		else{
			turno_tra_beta++;
		}	
		/* COMPLETARE */
		/* il prossimo corridore deve essere un alfa */
		turno_gruppo=TURNOALFA;
		/* COMPLETARE */
		/* sveglio gli alfa */	
		DBGpthread_cond_broadcast(&cond_alfa, Blabel);
		DBGpthread_mutex_unlock(&mutex, Blabel);
	}
	pthread_exit(NULL); 
}

int main(){
	int rc,i, *p;
	pthread_t th;
	
	rc = pthread_cond_init(&cond_alfa, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&cond_beta, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	
	/*creo i thread alfa*/
	for(i=0;i<NUM_ALFA;i++) {
        /* alloco la struttura in cui passare i parametri */
        p=malloc(sizeof(int));
        if(p==NULL) {
                perror("malloc failed: ");
                exit (1);
        }
        *p=i;
		rc=pthread_create( &th, NULL, alfa, (void*)p ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	/*creo i thread beta*/
	for(i=0;i<NUM_BETA;i++) {
        /* alloco la struttura in cui passare i parametri */
        p=malloc(sizeof(int));
        if(p==NULL) {
                perror("malloc failed: ");
                exit (1);
        }
        *p=i;
		rc=pthread_create( &th, NULL, beta, (void*)p ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 
	return 0;
}
