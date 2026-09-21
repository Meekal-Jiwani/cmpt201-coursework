#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	while(1){	
		char *string = NULL;
		size_t len = 0;
		char *saveptr;

		printf("Please enter some text: ");
		ssize_t read = getline(&string, &len, stdin);
	
		if(read == -1){
			perror("ERROR: No string provided");
			exit(EXIT_FAILURE);
		}

		char *token = strtok_r(string, " \n", &saveptr);
	
		printf("Tokens: ");
		while(token != NULL){
			printf("\n");
			printf("  %s",token);
			token = strtok_r(NULL, " \n", &saveptr);
		}

		printf("\n");
		free(string);
	}
	
	return 0;
}

