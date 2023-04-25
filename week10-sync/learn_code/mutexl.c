#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutexl = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void* functionC() {
	pthread_mutex_lock(&mutexl);
	counter++;
	printf("Counter value: %d\n", counter);
	pthread_mutex_unlock(&mutexl);
}

int main() {
	pthread_t thread1, thread2;
	
	pthread_create(&thread1, NULL, functionC, NULL);
	pthread_create(&thread2, NULL, functionC, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	exit(0);
}
