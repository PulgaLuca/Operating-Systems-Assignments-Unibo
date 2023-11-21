NCLUDEDIR=../INCLUDE
CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=
LIBRARIES=-lm

all: main.exe

main.exe: main.o dimezza.o quadrato.o
	gcc ${LFLAGS} -o main.exe main.o dimezza.o quadrato.o ${LIBRARIES}

main.o:	main.c ${INCLUDEDIR}/quadrato.h ${INCLUDEDIR}/dimezza.h
	gcc -c ${CFLAGS} -I${INCLUDEDIR} main.c

dimezza.o: dimezza.c
	gcc -c ${CFLAGS} dimezza.c

quadrato.o: quadrato.c
	gcc -c ${CFLAGS} quadrato.c

.PHONY: clean

clean:
rm -f main.exe main.o dimezza.o quadrato.o *~ core
