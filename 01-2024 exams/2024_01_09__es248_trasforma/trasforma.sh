#!/bin/bash

# Uno script trasforma.sh effettua le seguenti operazioni:
# - definisce una variabile var1 con valore A ed una variabile var2 con valore B.
# - legge dallo standard input delle righe che contengono ordini. 
#   Ciascuna riga contiene o due o tre parole e rappresenta un ordine impartito allo script.
#   Le parole lette da ciascuna riga vengono messe nelle variabili p1 p2 e p3,
#   con le ultime che possono essere vuote se la riga contiene meno di 3 parole.
# - dopo avere letto ciascuna riga, e collocato le parole nelle variabili p1 p2 e p3,
#   lo script interpreta l'ordine descritto nella riga letta.
# - Gli ordini possono essere solo i seguenti:
#   -- VISUALIZZA NOMEVAR
#   -- ASSEGNA NOMEVAR VALORE
#   dove NOMEVAR e' il nome di una delle due variabili var1 o var2.
#   dove VALORE e' una stringa di testo senza spazi, senza tabulazioni e caratteri speciali della bash.
#   Il comando VISUALIZZA mette sullo standard  output il contenuto della variabile il cui nome
#      e' specificato dal secondo argomento.
#   Il comando ASSEGNA modifica il contenuto della variabile specificata dal secondo argomento mettendo
#      come nuovo contenuto la stringa specificata come terzo argomento.
#
# Lo script trasforma.sh legge le righe prendendole da un file MIOINPUT.txt, quindi viene lanciato cosi':
#	./trasforma.sh < MIOINPUT.txt
# Un possibile file di input e' il seguente MIOINPUT.txt
#
# VISUALIZZA var1 
# ASSEGNA var1 CIAO
# VISUALIZZA var1 
# VISUALIZZA var2 
# ASSEGNA var2 PIPPO
# VISUALIZZA var2 
#
# Lanciando lo script come segue:
#	./trasforma.sh < MIOINPUT.txt
# deve dare come output le seguenti 4 righe:
# A
# CIAO
# B
# PIPPO
#
#

var1=A
var2=B

# VIC: completare a partire da qui.

while read p1 p2 p3 ; do 
	# se la riga non e' vuota
	if [[ -z $p1 ]] ; then
		continue
	elif [[ $p1 == "ASSEGNA" && -n $p2 && -n $p3 ]] ; then
		if [[ $p2 == "var1" ]] ; then
			var1=$p3
		elif [[ $p2 == "var2" ]] ; then
			var2=$p3
		fi
	elif [[ $p1 == "VISUALIZZA" && -n $p2 && -z $p3
		&& ( $p2 == "var1" || $p2 == "var2" ) ]] ; then

		echo ${!p2}
	fi

done

