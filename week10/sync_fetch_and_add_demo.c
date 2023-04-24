#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 设置是否使用原子操作
//int use_atomic_ops = 0;
int use_atomic_ops = 1;
int count = 0;

// 使用非原子操作来进行count
void* runner() {
	for (int i = 0; i < 1000000; i++) 
		count++;
	return 0;
}

// 使用原子操作来进行count
void* runner_sync() {
	for (int i=0; i<1000000; i++) 
		__sync_fetch_and_add(&count, 1);
	return 0;
}

int main() {
	// 创建16个线程进行计数
	pthread_t threadIDs[16];
	for (int i=0; i<16; i++) {
		if (use_atomic_ops) 
			pthread_create(&threadIDs[i], NULL, runner_sync, NULL);
		else
			pthread_create(&threadIDs[i], NULL, runner, NULL);
	}
	
	// 等待线程
	for (int i=0; i<16; i++) 
		pthread_join(threadIDs[i], NULL);
	
	// 带你输出结果
	if (use_atomic_ops) 
		printf("The atomic counter is %u\n", count);
	else
		printf("The nonatomic counter is %u\n", count);
}
