#!/bin/bash

while read RIGA ; do 
	WORD="&{RIGA%% *}"
	echo "${WORD}" 1>&2
#	echo "EVVIVA"
done
