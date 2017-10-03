#include <stdbool.h>
#include <stdio.h>


int main(int argc, char *argv[]){
	FILE *inputFile;
	FILE *outputFile;
	
	if(argc == 0){
		//grabs from command line

	}

	if(argc == 2){
		inputFile = argv[0];
		outputFile = argv[1];
	}

	if(argc != 0 && argc != 2){
		printf("Ya done goofed");
		return 1;
	}


	return 0;
}
