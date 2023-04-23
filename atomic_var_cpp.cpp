#include <iostream>
#include <pthread.h>
#include <atomic>

using namespace std;

atomic<bool> ready(false);
atomic<bool> winner(false);

void* count1m(void *arg) {
	int id = *(int *)arg;
	while(!ready);
	// 延迟时间
	for(int i=0; i<1000000; i++);
	
	// exchange函数用来修改变量的值
	// 返回值: 这个变量原来的值
	if (!winner.exchange(true)) 
		cout<< "thread # " << id <<" won!" <<endl;
	
	return NULL;
}

int main() {
	pthread_t threadIDs[10];
	cout<<"spawning 10 threads that count to 1 million..."<<endl;
	
	// 生成10个线程
	for(int i=0; i<10; i++) 
		pthread_create(&threadIDs[i], NULL, count1m, (void*)&i);

	ready = true;

	for(int i=0; i<10; i++)
		pthread_join(threadIDs[i], NULL);

	return 0;
}
