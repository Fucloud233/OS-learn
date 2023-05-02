#include "AtomicList.h"
#include <pthread.h>

AtomicList atomic_list;
// 定义每个线程操作的的最大次数
static int MAX_SIZE = 5;

// 从0开始 依次向链表添加元素
atomic<int> count(0);
void* atomic_list_push(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) 
		atomic_list.push(++count);
	return 0;
}

// 从链表中删除元素
void* atomic_list_pop(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) 
		atomic_list.pop();
	return 0;
}

int main () {
	int thread_num = 5;
	pthread_t threads[thread_num];
	
	// 使用5个线程向链表中添加元素
	for(int i=0; i<thread_num; i++) {
		pthread_create(&threads[i], NULL, atomic_list_push, NULL);
	}

	for(int i=0; i<thread_num; i++)
		pthread_join(threads[i], NULL);
	
	// 如果显示了5*5个数字 则运行正确
	atomic_list.display();
	
	thread_num = 3;
	// 使用3个线程从链表中删除元素
	for(int i=0; i<thread_num; i++)
		pthread_create(&threads[i], NULL, atomic_list_pop, NULL);
	
	for(int i=0; i<thread_num; i++)
		pthread_join(threads[i], NULL);
	
	// 如果显示了(5-2)*5个数字 则运行正确
	atomic_list.display();

}
