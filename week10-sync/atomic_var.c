#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

// 原子变量的基本操作都是以原子的方式完成的
_Atomic int atomic_count = 0;
int count = 0;

void* runner() {
	for(int i=0; i<1000000; i++) {
		count++;
		atomic_count++;
	}
	return 0;
}

int main() {
	pthread_t threadIDs[16];
	
	for(int i=0; i<16; i++) 
		pthread_create(&threadIDs[i], NULL, runner, NULL);

	for(int i=0; i<16; i++)
		pthread_join(threadIDs[i], NULL);
	
	printf("The atomic counter is %u\n", atomic_count);
	printf("The non-atomic counter is %u\n", count);
}
