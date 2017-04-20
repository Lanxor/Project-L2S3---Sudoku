# makefile de base

all: sudoku

sudoku: case.o grille.o regles.o main.o
	gcc -o sudoku case.o grille.o regles.o main.o

case.o: case.c case.h
	gcc -o case.o -c case.c

grille.o: grille.c case.h grille.h
	gcc -o grille.o -c grille.c

regles.o: regles.c case.h grille.h regles.h
	gcc -o regles.o -c regles.c

main.o: main.c case.h grille.h regles.h
	gcc -o main.o -c main.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf sudoku
