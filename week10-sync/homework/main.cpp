#include "AtomicList.h"
#include <pthread.h>

AtomicList atomic_list;
static int MAX_SIZE = 5;

void* atomic_list_push(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) 
		atomic_list.push(i);
	
	return 0;
}

void* atomic_list_pop(void* arg) {
	for(int i=0; i<MAX_SIZE; i++) 
		atomic_list.pop();
	return 0;
}

int main () {
	int thread_num = 4;
	pthread_t threads[thread_num];

	for(int i=0; i<thread_num; i++) 
		pthread_create(&threads[i], NULL, atomic_list_push, NULL);
	
	for(int i=0; i<thread_num; i++)
		pthread_join(threads[i], NULL);

	atomic_list.display();

}
