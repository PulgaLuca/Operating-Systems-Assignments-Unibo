#!/bin/bash

sed 's/ciao 1/ciao 2/g' d1/m1.c > d2/m2.c
sed 's/m1/m2/g' d1/Makefile > d2/Makefile2

make -C d1 -f Makefile
make -C d2 -f Makefile2

d1/m1.exe
d2/m2.exe
