all: assembler.o main-assembler.c assembler.h
	gcc -Wall main-assembler.c assembler.o -o myasm

assembler.o: assembler.c assembler.h
	gcc -Wall assembler.c -c
