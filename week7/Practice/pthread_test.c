#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *argv) {
	int *num = (int *)malloc(sizeof(int));
	*num = *(int*)argv + 1;

	pthread_exit((void *)num);

	return (void *)num;
}

int main() {
	pthread_t thread;

	int n = 5, *res;
	pthread_create(&thread, NULL, thread_func, &n);

	pthread_join(thread, (void *)&res);

	printf("Result: %d\n", *res);
	
	printf("the next funciton: ");
	int n2 = 7;

	int res2 = *(int *) thread_func((void *)&n2);
	printf("Result: %d\n", res2);
}
