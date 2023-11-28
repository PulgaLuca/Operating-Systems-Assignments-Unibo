#!/bin/bash

#Scrivere poi lo script star.sh che deve leggere una per una le righe provenienti
#dallo standard input e stampare a video, per ciascuna riga, la quarta e la terza
#parola della riga, in quest'ordine, separate da spazi.
#L'output dovrà essere :
#quattro tre
#gamma *
#four three
#Lanciare lo script star.sh passandogli nello standard input il contenuto del file
#asterischi.txt. Verificare che l'output sia corretto.

exec {FD}< "$1"
if (( $? == 0 )); then
	while read -u ${FD} A B C D ; do
		if [[ ${D} != "" && ${C} != "" ]] ; then
			echo "${D} ${C}"
		else
			echo "3° or 4° parameter missing"
		fi
	done
	exec {FD}>&-
fi
