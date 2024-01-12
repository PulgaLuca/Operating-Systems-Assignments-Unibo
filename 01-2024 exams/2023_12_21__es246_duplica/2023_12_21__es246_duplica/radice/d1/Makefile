CFLAGS=-ansi -Wpedantic -Wall

all: 	 m1.exe

m1.exe:  m1.o
	gcc -o m1.exe m1.o

m1.o: m1.c
	gcc -c ${CFLAGS} m1.c 

.PHONY:	clean

clean:
	-rm -f m1.o m1.exe


