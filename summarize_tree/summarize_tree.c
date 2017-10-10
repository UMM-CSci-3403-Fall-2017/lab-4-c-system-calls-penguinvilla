#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int num_dirs, num_regular;
bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
//	char cwd[1024];
	DIR *dir;
        dir = opendir(path);
	int chdirRes;
	printf("made it to process_directory %s\n", path);
//	getcwd(cwd, sizeof(cwd));
//	printf("Before chdir: %s\n", cwd);
	chdirRes = chdir(path);
//	getcwd(cwd, sizeof(cwd));
//	printf("After chdir: %s code: %d and path: %s\n", cwd, chdirRes, path);
	if(dir == NULL){
		printf("Cannot open directory %s error code: %d\n", path, errno);
		return;
	}

	struct dirent* file;
        file = readdir(dir);
	while (file != NULL){
		if (strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0 ){
			process_path(file->d_name);
		}

		file = readdir(dir);
	}
	num_dirs++;
	chdir("..");
	closedir(dir);
	free(file); free(dir);
}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
	printf("made it to process_file %s\n",path);
	num_regular++;
}

void process_path(const char* path) {
	printf("made it to process_path! %d\n", num_dirs + num_regular);
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("first dir : %s\n", cwd);
  num_dirs = 0;
  num_regular = 0;

  
  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
