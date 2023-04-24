#include <iostream>
#include <atomic>
#include <pthread.h>

using namespace std;

atomic<unsigned long> a = 0;

void *routine(void *arg) {
	for(int i=0; i<1000000000; i++) 
		a++;
//	cout<< a << endl;
	return NULL;
}

int main(void) {
	int thread_num = 8;
	pthread_t threads[thread_num];

	for(int i=0; i<thread_num; i++)
		pthread_create(&threads[i], NULL, routine, 0);
	
	for(int i=0; i<thread_num; i++) { 
		pthread_join(threads[i], NULL);
//		cout<< i << endl;
	}
	
	cout<< a <<endl;
}
