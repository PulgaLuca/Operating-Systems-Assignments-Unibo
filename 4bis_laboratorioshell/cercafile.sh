#!/bin/bash
for char in {c..g} ; do
	for file in /usr/include/?${char}* ; do
		if [[ -e ${file} && (( ${#file} -lt 18 || ${#file} -gt 23 )) ]] ; then
			echo "${file} with ${char}";
		fi
	done
done
