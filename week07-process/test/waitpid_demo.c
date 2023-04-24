#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int rc = fork();
	if(rc < 0) {
		// 通过stderr流输出
		fprintf(stderr, "Fork failed\n");
		exit(-1);
	}
	else if(rc == 0) 
		printf("Child process: existing\n");
	else {
		int status = 0;
		if(waitpid(rc, &status, 0) < 0) 
			fprintf(stderr, "waitpid failed\n");
		// 判断子线程是否结束了
		if(WIFEXITED(status)) 
			printf("Parent process: my child process has exited\n");
		else
			fprintf(stderr, "Parent processes: waitpid returns for unknown reasons\n");
	}
}
		
