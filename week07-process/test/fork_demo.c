#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char str[11] = {0};

int main(int argc, char* argv[]) {
	int fd = open("test.tx", O_RDWR);
	if(fork() == 0) {
		ssize_t cnt = read(fd, str, 10);
		printf("Child process: %s\n", str);
	}
	else {
		ssize_t cnt = read(fd, str, 10);
		printf("Parent process: %s\n", str);
	}
	close(fd);
	return 0;
}
