#!/bin/bash

#Scrivere uno script bash leggerecaratteri.sh che legge uno per uno i caratteri del
#file /usr/include/stdio.h e stampa a video il numero dei caratteri letti dal file

exec {FD}<"/usr/include/stdio.h"
if(($?==0));then
	NUM=0
	while read -u ${FD} -N 1 -r A ; do 
		((NUM=${NUM}+1))
	done
	exec {FD}>&-
	echo "CHAR NUM: ${NUM}"
fi

# same with: wc -c /usr/incluse/stdio.h
