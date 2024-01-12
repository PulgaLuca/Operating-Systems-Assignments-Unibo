#!/bin/bash

#Scrivere uno script puntini.sh che prende come argomento a riga di comando un
#intero positivo che rappresenta un certo numero di secondi. Lo script deve rimanere
#in esecuzione per quel numero di secondi e, ad ogni secondo, stampare a video un
#punto . seguito dal proprio PID. Ma senza andare a capo
NUM=0
#if [[ $1 != "" ]] ; then echo "Insert an integer at least" ; exit 1 ; fi
while (( ${NUM} < $1 )) ; do
	sleep 1
	echo -n ".${BASHPID}"
	(( NUM=${NUM}+1 ))
done
echo ""
