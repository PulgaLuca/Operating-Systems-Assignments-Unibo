#!/bin/bash

FILES=`find /usr/include/linux/ -maxdepth 1 -name "*f*.h" -print`
if [[ -z ${FILES} ]] ; then echo "no files found" ; exit 1 ; fi
for FILE in ${FILES} ; do
	ROWS=`wc -l ${FILE}`
	ROWS=${ROWS%% *}
	if [[ ${ROWS} -ge 10 && ${ROWS} -le 100 ]] ; then
		LAST=`tail -n 1 ${FILE} | wc -m`
		echo "${LAST}"
	fi
done
