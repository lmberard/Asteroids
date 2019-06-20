CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2
INSTALL_DIR := /usr/sbin

all: tp2

naves.o: naves.c naves.h 
	$(CC) $(CFLAGS) naves.c

caracteres.o: caracteres.c caracteres.h naves.h
	$(CC) $(CFLAGS) caracteres.c

movimientos.o: movimientos.c movimientos.h
	$(CC) $(CFLAGS) movimientos.c

vectores.o: vectores.c vectores.h
	$(CC) $(CFLAGS) vectores.c

diccionario.o: diccionario.h diccionario.c
	$(CC) $(CFLAGS) diccionario.c

renderizar.o: renderizar.c renderizar.h diccionario.h
	$(CC) $(CFLAGS) renderizar.c


main.o: main.c config.h naves.h movimientos.h diccionario.h vectores.h renderizar.h
	$(CC) $(CFLAGS) main.c

tp2: main.o naves.o caracteres.o movimientos.o vectores.o diccionario.o renderizar.o 
	$(CC) $(LFLAGS) $^ -o tp2 -lSDL2 -lm

clean:
	rm *.o

install: tp2
	cp $^ $(INSTALL_DIR)

valgrind: tp1
	valgrind --leak-check=full ./tp1
