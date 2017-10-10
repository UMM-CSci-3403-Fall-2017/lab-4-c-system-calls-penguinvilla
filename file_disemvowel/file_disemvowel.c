#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

/* takes a char, returns true if that char is  a vowel and false otherwise */
bool is_vowel(char ch){
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
                || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

/* takes the number of chars in a file,, the file, and a file to read into,
 *  and puts all the non-vowel chars into the second file  */
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf){
	int j = 0;
	for (int i = 0; i < num_chars; ++i){
		if(!is_vowel(in_buf[i])){
			out_buf[j] = in_buf[i];
			++j;
		}
	}
	return j;
}
/* takes an input file, removes all the vowels, and puts that into the given output file  */
int disemvowel(FILE* inputFile, FILE* outputFile){
	int num_chars;
	int num_cons;
	char in_buf[BUF_SIZE];

	num_chars = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
	char out_buf[num_chars];
	num_cons = copy_non_vowels(num_chars, in_buf, out_buf);

	fwrite(out_buf, sizeof(char), num_cons, outputFile);
	
	return num_cons;
}

int main(int argc, char *argv[]){
	FILE *inputFile;
	FILE *outputFile;
	int num_cons;

	if(argc == 1){
		//grabs from command line
		inputFile = fopen("tempFile", "w");
		inputFile = stdin;
		outputFile = fopen("tempOut", "w+");
	} else if(argc == 2){
		//reads from file to stdout
		inputFile = fopen(argv[1], "r");
		outputFile = fopen("tempOut", "w+");
	} else if(argc == 3){
		//reads to file, writes to file
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	} else {
		printf("Incorrect number arguments. You used %d and must have 2 or less", argc - 1);
		return 1;
	}

	num_cons = disemvowel(inputFile, outputFile);

	if(argc == 2 || argc == 1){
		//remove files and prints to standard out
		char* paragraph = malloc(BUF_SIZE * sizeof(char));
		fseek(outputFile, 0, SEEK_SET);
		fread(paragraph, sizeof(char), num_cons - 1, outputFile);
		printf("%s\n", paragraph);

		remove("tempFile");
		remove("tempOut");
		free(paragraph);
		
	}
	fclose(inputFile);
	fclose(outputFile);

	return 0;
}
