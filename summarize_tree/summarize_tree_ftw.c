#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>

static int num_direct, num_file;
static int callback(const char *fpath, const struct stat *sb, int typeflag) { 
	// Define stuff here 
	
	if (typeflag == FTW_D) {
		num_direct++;
		return 0;
	} else {
		num_file++;
		return 0;
	}
	return 1;
}
    
#define MAX_FTW_DEPTH 16
    
int main(int argc, char** argv) { 
	// Check arguments and set things up
	num_direct = 0;
	num_file = 0;
	if(argc != 2){
		printf("wrong number of arguments\n");
		return 1;
	}

	ftw(argv[1], callback, MAX_FTW_DEPTH);
    
	// Print out the results
	printf("There were %d directories.\n", num_direct);
	printf("There were %d regular files.\n", num_file);
	return 0;
}
