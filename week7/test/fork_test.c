#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char str[11] = {0};

int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDWR);
	// 子线程和父线程共享了同一个指向文件的结构体
	if(fork() == 0) {
		ssize_t cnt = read(fd, str, 10);
		printf("Child process: %s\n", str);

		write(fd, "hello", 5);
	}
	else {
		ssize_t cnt = read(fd, str, 10);
		printf("Parent process: %s\n", str);
		write(fd, "world", 5);
	}
	close(fd);
	return 0;
}
