#!/bin/bash

# Si scrivano 3 script: generacar.sh, init.sh e forsericorsione.sh
#
# Lo script generacar.sh stampa in output un carattere casuale in {'a','t','x'} ed e' gia' fornito.
#
# Un altro script forsericorsione.sh crea e stampa in output una stringa formata da
# - un carattere iniziale ed un carattere finale (uguali tra loro) generati
#   chiamando lo script generacar.sh.
# - una parte centrale formata da 2*(N-1) caratteri che viene creata
#   chiamando opportunamente lo stesso script forsericorsione.sh
# NB: Ogni istanza del processo forsericorsione.sh puo' effettuare
#     DIRETTAMENTE solo una chiamata allo script stesso forsericorsione.sh.
# NB: Inoltre, lo script forsericorsione.sh NON PUO' PRENDERE ARGOMENTI A RIGA DI COMANDO.
#
# Un terzo script init.sh e' quello che fa partire l'esecuzione, settando il necessario
# e lanciando la prima volta lo script forsericorsione.sh
# Questo script non consente di usare parametri a riga di comando.
# Lo script init deve fare il necessario per far generare e stampare sullo standard output
# una stringa di lunghezza 2*4.

CAR=$(./generacar.sh)
((NUM=${NUM}-1))
if (( $NUM > 0 )) ; then
	echo -n "${CAR}$(./forsericorsione.sh)${CAR}"
else
	echo -n "${CAR}${CAR}"
fi
exit 0


