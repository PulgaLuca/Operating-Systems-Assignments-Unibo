#!/bin/bash

# Scrivere uno script lettera.sh che genera ad ogni invocazione
# una lettera a caso tra queste due a c
# e la stampa in output SENZA ANDARE A CAPO.
# Suggerimento: usare variabile RANDOM.

(( NUM=${RANDOM}%2 ))
if (( ${NUM}==0 )) ; then
	echo -n "a"
else
	echo -n "c"
fi
