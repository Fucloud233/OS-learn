#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // return the pid
    int rc = fork();

    if(rc < 0) {
	fprintf(stderr, "Fork failed\n");
    }
    else if (rc == 0) {
	printf("Child process: existing\n");
    }
    else {
	int status = 0;
	if(waitpid(rc, &status, 0) < 0 ){
	    fprintf(stderr, "Parent process: waitpid failed\n");
	    exit(-1);
	}

	if(WIFEXITED(status)) {
	    printf("Parent process: my child has exited\n");
	}
	else {
	    fprintf(stderr, "Parent process: waitpid returns for unknown reasons\n");
	}
    }
}
