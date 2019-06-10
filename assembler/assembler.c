#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"

char determineCodeOp(char *instruction, int *nbReg) {
	char codeOp = 0;
	if (strstr(instruction, "ADD") != NULL) {
		codeOp = 0x00;
		*(nbReg) = 3;
	} else
	if (strstr(instruction, "SUB") != NULL) {
		codeOp = 0x01;
		*(nbReg) = 3;
	} else
	if (strstr(instruction, "SET") != NULL) {
		codeOp = 0x02;
		*(nbReg) = 1;
	} else
	if (strstr(instruction, "LDB") != NULL) {
		codeOp = 0x03;
		*(nbReg) = 1;
	} else
	if (strstr(instruction, "STB") != NULL) {
		codeOp = 0x04;
		*(nbReg) = 1;
	} else
	if (strstr(instruction, "SLL") != NULL) {
		codeOp = 0x05;
		*(nbReg) = 1;
	} else
	if (strstr(instruction, "SLR") != NULL) {
		*(nbReg) = 1;
	} else
	if (strstr(instruction, "BEQ") != NULL) {
		codeOp = 0x07;
		*(nbReg) = 2;
	} else
	if (strstr(instruction, "B") != NULL) {
		codeOp = 0x08;
		*(nbReg) = 0;
	} else
	if (strstr(instruction, "OUT") != NULL) {
		codeOp = 0x09;
		*(nbReg) = 2;
	} else
	if (strstr(instruction, "IN") != NULL) {
		codeOp = 0x0A;
		*(nbReg) = 2;
	}
	return codeOp;
}

char *determineUsedReg(char *instruction, int nbReg) {
	char *r = malloc((nbReg + 1) * sizeof(char));
	if (r == NULL) {
		fprintf(stderr, "Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	r[nbReg] = '\0';
	int i, j = 0;
	int l = strlen(instruction);
	for (i = 0 ; i < l - 1 ; i++) {
		if (instruction[i] == 'r') {
			r[j] = instruction[i+1] - '0';
			j++;
			if (j > nbReg) {
				fprintf(stderr, "Error : too much registers in instruction : %s\n", instruction);
				exit(EXIT_FAILURE);
			}
		}
	}
	return r;
}

void determineIOReg(char codeOp, char* usedR, char** inReg, char** outReg) {
	switch(codeOp) {
		case ADD:
		case SUB:
			*outReg = malloc(1 * sizeof(char));
			*inReg = malloc(2 * sizeof(char));
			(*outReg)[0] = usedR[0];
			(*inReg)[0] = usedR[1];
			(*inReg)[1] = usedR[2];
			break;
		case SET:
			*outReg = malloc(1 * sizeof(char));
			(*outReg)[0] = usedR[0];
			break;
		case LDB:
			*outReg = malloc(1 * sizeof(char));
			(*outReg)[0] = usedR[0];
			break;
		case STB:
			*inReg = malloc(1 * sizeof(char));
			(*inReg)[0] = usedR[0];
			break;
		case SLL:
		case SLR:
			*inReg = malloc(1 * sizeof(char));
			*outReg = malloc(1 * sizeof(char));
			(*inReg)[0] = usedR[0];
			(*outReg)[0] = usedR[0];
			break;
		case BEQ:
			*inReg = malloc(2 * sizeof(char));
			*inReg = usedR;
			break;
		case IN:
			*inReg = malloc(2 * sizeof(char));
			(*inReg)[0] = usedR[0];
			(*inReg)[1] = usedR[1];
			break;
		case OUT:
			*outReg = malloc(1 * sizeof(char));
			(*outReg)[0] = usedR[0];
			(*outReg)[1] = usedR[1];
			break;
	}
}

unsigned char *genInstruction(char codeOp, char *inReg, char *outReg, int val) {
	unsigned char *cmd;
	cmd = (unsigned char*)malloc(2 * sizeof(char));
	switch (codeOp) {
		case ADD:
		case SUB:
			cmd[0] = (codeOp << 4) + outReg[0];
			cmd[1] = (inReg[0] << 4) + inReg[1];
			break;
		case SET:
		case SLL:
		case SLR:
			cmd[0] = (codeOp << 4) + outReg[0];
			cmd[1] = (unsigned char)val;
			break;
		case LDB:
			cmd[0] = (codeOp << 4) + outReg[0];
			cmd[1] = (unsigned char)val;
			break;
		case STB:
			cmd[0] = (codeOp << 4) + inReg[0];
			cmd[1] = (unsigned char)val;
			break;
		case BEQ:
			cmd[0] = (codeOp << 4) + inReg[0];
			cmd[1] = (inReg[1] << 4) + val;
			break;
		case B:
			cmd[0] = (codeOp << 4) + ((val >> 8) & 0x0F);
			cmd[1] = (val & 0x0FF);
			break;
		case IN:
			cmd[0] = (codeOp << 4) + inReg[0];
			cmd[1] = (inReg[1] << 4);
			break;
		case OUT:
			cmd[0] = (codeOp << 4) + outReg[0];
			cmd[1] = (outReg[1] << 4);
			break;
	}
	return cmd;
}

int determineVal(char *instruction, int nbReg) {
	int val = 0;
	char *start;
	start = strstr(instruction, "0x");

	if (nbReg == 2) { //BEQ
		if (start != NULL) {
			val+= ASCII2D(start[2]);
		}
	} else if (nbReg == 1) { // SET
		if (start != NULL) {
			val += ASCII2D(start[2]) * 16 + ASCII2D(start[3]);
		}
	} else if (nbReg == 0) { // B 
		if (start != NULL) {
			val += ASCII2D(start[2]) * 16 * 16 + ASCII2D(start[3]) * 16 + ASCII2D(start[4]);
		}
	}
	return val;
}

char ASCII2D(char c) {
	char d = 0;
	if (c >= '0' && c <= '9') {
		d = c - '0';
	} else if (c >= 'A' && c <= 'F') {
		d = c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		d = c - 'a' + 10;
	}
	return d;
}
