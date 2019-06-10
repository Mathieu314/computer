#ifndef ASSEMBLER
#define ASSEMBLER

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


char determineCodeOp(char *instruction, int *nbReg);
char *determineUsedReg(char *instruction, int nbReg);
void determineIOReg(char codeOP, char *usedR, char **inReg, char **outReg);
unsigned char *genInstruction(char codeoP, char *inReg, char *outReg, int val);
int determineVal(char *instruction, int nbReg);
char ASCII2D(char c);

#endif
