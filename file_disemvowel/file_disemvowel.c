#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

/* takes a char, returns true if that char is  a vowel and false otherwise */
bool is_vowel(char ch){
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
                || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}


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
		
		
	} else if(argc == 3){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	} else {
		printf("Incorrect number arguments. You used %d and must have 2 or less", argc - 1);
		return 1;
	}

	num_cons = disemvowel(inputFile, outputFile);

	if(argc == 2 || argc == 1){
		char* line = malloc(BUF_SIZE * sizeof(char));
	//	size_t size = BUF_SIZE;
		fseek(outputFile, 0, SEEK_SET);
	//	fwrite(outputFile, sizeof(char), BUF_SIZE, stdout);
	
//		while(getline(&line, &size, outputFile) > 0 ){
//			printf("%s\n", line);
//		}
//
		fread(line, sizeof(char), num_cons - 1, outputFile);
//		line = realloc(line, sizeof(char) * (size - 1));
		printf("%s\n", line);

		remove("tempFile");
		remove("tempOut");
		free(line);
	//remove files and write to standard out
	}

	return 0;
}
