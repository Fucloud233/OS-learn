#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int use_atomic_ops = 0;
int count = 0;

void* runner() {
	for (int i = 0; i < 1000000; i++) 
		count++
	return 0;
}

void* runner_sync() {
	for (int i=0; i<1000000; i++) {
		__sync_fetch_and_add(&count, 1);
	}
	return 0;
}

int main() {
	pthread_t threadIDs[16];
	for (int i=0; i<16; i++) {
		if (user_atomic_ops) 
			pthread_create(&threadIDs[i], NULL, runner_sync, NULL);
		else
			pthread_create(&threadIDs[i], NULL, runner, NULL);
	}

	for (int i=0; i<16; i++) 
		pthread_join(threadIDs[i], NULL);

	if (use`
