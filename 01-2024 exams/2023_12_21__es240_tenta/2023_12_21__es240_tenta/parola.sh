#!/bin/bash

# Scrivere poi uno script parola.sh che usa piu' volte
# il precedente script lettera.sh
# per generare parole formate da quattro caratteri
# e visualizzarle sul proprio stdout.

PAROLA=""
for (( i=0; $i < 4; i=$i + 1 )) ; do
	PAROLA=${PAROLA}`./lettera.sh`
done
echo ${PAROLA}
