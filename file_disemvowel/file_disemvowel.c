#include <stdbool.h>
#include <stdio.h>

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

void disemvowel(FILE* inputFile, FILE* outputFile){
	int num_chars;
	int num_cons;
	char in_buf[BUF_SIZE];

	num_chars = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
	char out_buf[num_chars];
	num_cons = copy_non_vowels(num_chars, in_buf, out_buf);

	fwrite(out_buf, sizeof(char), num_cons, outputFile);
}

int main(int argc, char *argv[]){
	FILE *inputFile;
	FILE *outputFile;
	
	if(argc != 1 && argc != 3){
		printf("Ya done goofed");
		return 1;
	}

	if(argc == 1){
		//grabs from command line

	}

	if(argc == 3){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	}

	disemvowel(inputFile, outputFile);

	return 0;
}
