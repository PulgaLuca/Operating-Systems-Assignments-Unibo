#!/bin/bash
for name in *
do
	echo "filename is: ${name}"
	ls -ld ${name}
done
