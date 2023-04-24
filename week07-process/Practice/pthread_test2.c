#include <stdio.h>
#include <pthread.h>

int main() {
	printf("Running");
	pthread_exit(NULL);
	printf("Exit");
}
