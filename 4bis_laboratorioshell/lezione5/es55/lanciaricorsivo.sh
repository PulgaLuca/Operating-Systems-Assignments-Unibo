#!/bin/bash

#Creare uno script lanciaricorsivo.sh che necessita di un unico argomento intero
#che è il numero totale di processi discendenti che rimangono ancora da lanciare.
#Se il numero di discendenti da lanciare è maggiore di zero allora lo script lancia in
#background una nuova istanza di sé stesso passando come argomento il proprio
#argomento diminuito di 1.
#Lanciato il figlio, il padre visualizza in output il pid del figlio, poi aspetta che il
#proprio figlio termini la propria esecuzione.
#Il figlio nel frattempo crea un suo figlio (un nipote del primo) il quale etc etc.
#Lanciare inizialmente lo script passandogli 5 come argomento.

if (( $1 > 0 )) ; then
	./lanciaricorsivo.sh $(( $1-1 )) &
	echo "PID: "$!
	wait $!
fi
