#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int global_resource;

// 使用加法
void* thread_inc (void* arg) {
    pthread_mutex_t* mutexl = (pthread_mutex_t *)arg;
	
	// lock
	pthread_mutex_lock(mutexl);
    
	for (int i = 0; i < 10; i++) {
        global_resource++;
        printf("Increment: %d\n", global_resource);
        sleep(1);
    } 
    printf("Thread inc finished.\n");
 
	// unlock
	pthread_mutex_unlock(mutexl);
	return NULL;
}

// 使用减法
void* thread_dec (void* arg) {
	pthread_mutex_t* mutexl = (pthread_mutex_t *)arg;
	
	// lock
	pthread_mutex_lock(mutexl);
    for (int i = 0; i < 10; i++) {
        global_resource--;
        printf("Decrement: %d\n", global_resource);
    }
    printf("Thread dec finished.\n");

	// unlock
	pthread_mutex_unlock(mutexl);
    return NULL;
}

int main (int argc, char** argv) {
	pthread_mutex_t mutexl = PTHREAD_MUTEX_INITIALIZER;
	
	pthread_t threads[2];
    pthread_create(&threads[0], NULL, thread_inc, (void *)&mutexl);
    pthread_create(&threads[1], NULL, thread_dec, (void *)&mutexl);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    return EXIT_SUCCESS;
}
