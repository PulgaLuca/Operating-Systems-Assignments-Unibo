#!/bin/bash

mkdir BUTTAMI
chmod 700 BUTTAMI/
touch BUTTAMI/"*" BUTTAMI/"**" BUTTAMI/"***" BUTTAMI/";;"
cd BUTTAMI/
ls ./
for file in ./* ; do touch "${file}.txt" ; done
cp -rf /usr/include ./
find ./ type -d
rm -rf ./include
