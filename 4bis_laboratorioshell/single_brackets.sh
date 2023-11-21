#!/bin/bash
name="$1" # passed param
if [ -e ${name} ] ; then
	echo "esiste";
else
	echo "${name} doesn't exist";
fi
