#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Error assembling : please provide a file to assemble\n");
		exit(EXIT_FAILURE);
	} else if(argc > 2) {
		fprintf(stderr, "Error assembling : too much arguments\n");
		exit(EXIT_FAILURE);
	}
	printf("Assembling %s ...\n\n", argv[1]);

	// Open and read file
	FILE *assemb = NULL;
	assemb = fopen(argv[1], "r");
	if (assemb == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}
	char *instruction = NULL;
	

	int nbReg = 0, val;
	char *inReg = NULL;
	char *outReg = NULL;
	char codeOp;
	char *r;
	size_t len = 0;
	unsigned char *cmd;
	int adr = 0;

	// for each line of instruction
	while (getline(&instruction, &len, assemb) != -1) {
		
		// Determine code op
		codeOp = determineCodeOp(instruction, &nbReg);

		// Determine I/O registers
		r = determineUsedReg(instruction, nbReg);
		determineIOReg(codeOp, r, &inReg, &outReg);
		
		// Determine val
		val = determineVal(instruction, nbReg);

		// Generate instruction code
		cmd = genInstruction(codeOp, inReg, outReg, val);

		// Print instruction hexadecimal code
		if (adr < 16) {
			printf("0x0%x\t|\t", adr);
		} else {
			printf("0x%x\t|\t", adr);
		}
		if (cmd[0] < 16) {
			printf("0x0%x", cmd[0]);
		} else {
			printf("0x%x", cmd[0]);
		}
		if (cmd[1] < 16) {
			printf("0%x", cmd[1]);
		} else {
			printf("%x", cmd[1]);
		}
		printf("\t|\t%s", instruction);
		
		adr += 2;
	}

	fclose(assemb);
	free(outReg);
	free(inReg);
	return 0;

}
