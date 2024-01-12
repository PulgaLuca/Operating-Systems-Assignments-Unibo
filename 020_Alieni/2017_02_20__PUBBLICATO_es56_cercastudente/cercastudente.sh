#!/bin/bash

EMAIL=$1
MAT=$2
if [[ "$#" != 2 ]] ; then echo "2 args needed" ; exit 1 ; fi
while read NOME COGNOME MATR CORSO ; do 
	if [[ ${MAT} -eq ${MATR} ]] ; then
		echo "la account ${EMAIL} appartiene allo studente ${NOME} ${COGNOME}"
	fi
done < matricola.txt
