#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if(argc != 2) 
		exit(EXIT_FAILURE);

	char* new_argv[] = {NULL, "hello", "world", NULL};
	char* new_env[] = {NULL};
	new_argv[0] = argv[1];

	execve(argv[1], new_argv, new_env);
	// 程序运行不到这里
	exit(EXIT_FAILURE);
}
