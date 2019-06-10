#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

int testPattern() {
	return 0;
}

char *removeNewLines(char *fileName) {
	// Open and read file
	FILE *cFile = NULL;
	cFile = fopen(fileName, "r");
	if (cFile == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}
	char *instruction = NULL;
	char *output = NULL;
	size_t len = 0;
	
	getline(&instruction, &len, cFile);
	output = (char*)malloc(strlen(instruction)-1);
	instruction[strlen(instruction)-1] = '\0';
	strcpy(output, instruction);

	while (getline(&instruction, &len, cFile) != -1) {
		output = (char*)realloc(output, strlen(output) + strlen(instruction));
		instruction[strlen(instruction)-1] = '\0';
		strcat(output, instruction);

	}
	fclose(cFile);
	return output;
}

char **getSymbols(char *source) {
	int i = 0;
	char **charTable;
	char charS[] = "char";
	int m = 0;
	int nbChar = 0;
	charTable = (char **)malloc(20 * sizeof(char*));
	for (i = 0 ; i < 20 ; i++) {
		charTable[i] = (char*)malloc(20 * sizeof(char));
	}
	char *c = (char*)malloc(sizeof(char));
	while (source[i] != '\0') {
		if (source[i] == charS[m]) {
			m++;
			i++;
			while(source[i] == charS[m] && charS[m] != '\0') {
				m++;
				i++;
			}
			if (charS[m] == '\0') {
				// char a...;
				m = 0;
				while (source[i] != ';') {
					charTable[nbChar][m] = source[i];
					//c = (char*)realloc(c, strlen(c) + 1);
					//c[m] = source[i];
					m++;
					i++;
				}
				charTable[nbChar][m] = '\0';
				//c[m] = '\0';
				//printf("%s\n", c);
				//realloc(charTable , sizeof(charTable) + 20*sizeof(char));
				//strcpy(charTable[nbChar], c);
				
				nbChar++;
			}
			charTable[nbChar][0] = '\0';
			//c[0] = '\0';
			//c = (char*)realloc(c, sizeof(char));
			m = 0;
		}
		i++;
	}
	printf("\n3 : %s\n", charTable[0]);
	printf("4 : %s\n", charTable[1]);

	return charTable;		
}
