#!/bin/bash

#Scrivere uno script bash leggerecaratteri.sh che legge uno per uno i caratteri del
#file /usr/include/stdio.h e stampa a video il numero dei caratteri letti dal file

exec {FD}< /usr/include/stdio.h
TOT=0
if (( $? == 0 )) ; then
	while read -u ${FD} -N 1 -r C ; do
		(( TOT=${TOT}+1 ))
	done
	exec {FD}>&-
fi
echo ${TOT}

#wc -c /usr/include/stdio.h
