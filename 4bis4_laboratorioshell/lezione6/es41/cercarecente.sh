#!/bin/bash

FILES=`find /usr/include/linux/ -mindepth 2 -name "*.h" -print`
if [[ -z ${FILES} ]] ; then 
	echo "nothing found :("
else
	CURR=""
	for CURR in ${FILES} ; do
		break
	done
	for FILE in ${FILES} ; do
		if [[ ${FILE} -nt ${CURR} ]] ; then
			CURR=${FILE}
		fi
	done
fi
echo "${CURR}"
