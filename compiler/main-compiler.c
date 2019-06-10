#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Error compiling : please provide a file to compile\n");
		exit(EXIT_FAILURE);
	} else if(argc > 2) {
		fprintf(stderr, "Error compiling : too much arguments\n");
		exit(EXIT_FAILURE);
	}
	printf("Compiling %s ...\n\n", argv[1]);

	char *source;
	char **symbols;
	
	// Create single line containing the whole code
	source = removeNewLines(argv[1]);

	symbols = getSymbols(source);
	printf("%s\n", symbols[0]);
	printf("%s\n", symbols[1]);

	free(source);
	return 0;

}
