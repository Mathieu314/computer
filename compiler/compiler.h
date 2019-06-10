#ifndef COMPILER
#define COMPILER

#define ADD 0
#define SUB 1
#define SET 2
#define LDB 3
#define STB 4
#define SLL 5
#define SLR 6
#define BEQ 7
#define B   8
#define OUT 9
#define IN  10

int testPattern();
char **getSymbols();
char *removeNewLines(char *fileName);

#endif
