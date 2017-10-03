#include <stdbool.h>
#include <stdio.h>

#define BUF_SIZE 1024

bool is_vowel(char c){

}

int copy_non_vowels(int num_chars, char* in_buf, char*out_buf){

}

void disemvowel(FILE* inputFile, FILE* outputFile){

}

int main(int argc, char *argv[]){
	FILE *inputFile;
	FILE *outputFile;
	
	if(argc != 0 && argc != 2){
		printf("Ya done goofed");
		return 1;
	}

	if(argc == 0){
		//grabs from command line

	}

	if(argc == 2){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	}

	disemvowel(inputFile, outputFile);

	return 0;
}
