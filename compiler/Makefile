all: compiler.o main-compiler.c compiler.h
	gcc -Wall main-compiler.c compiler.o -o mycc

compiler.o: compiler.c compiler.h
	gcc -Wall compiler.c -c
