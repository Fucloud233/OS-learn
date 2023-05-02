#include "AtomicList.h"
#include <pthread.h>

AtomicList atomic_list;
static int MAX_SIZE = 3;

atomic<int> count(0);

void* atomic_list_push(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) {
		count++;
		atomic_list.push(count);
	
	}
	return 0;
}

void* atomic_list_pop(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) 
		atomic_list.pop();
	return 0;
}

int main () {
	int thread_num = 5;
	pthread_t threads[thread_num];
	
	// 使用5个线程添加元素
	for(int i=0; i<thread_num; i++) {
		pthread_create(&threads[i], NULL, atomic_list_push, NULL);
	}

	for(int i=0; i<thread_num; i++)
		pthread_join(threads[i], NULL);

	atomic_list.display();
	
	thread_num = 3;
	// 使用3个线程删除链表中所有元素
	for(int i=0; i<thread_num; i++)
		pthread_create(&threads[i], NULL, atomic_list_pop, NULL);
	
	for(int i=0; i<thread_num; i++)
		pthread_join(threads[i], NULL);

	atomic_list.display();

}
