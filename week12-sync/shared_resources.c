#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 

pthread_mutex_t lock;
int shared_resource = 0;

void *thread1(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Thread 1 acquired lock\n");
    while (shared_resource == 0) {
        printf("Thread 1 waiting for shared resource\n");
        sleep(1);
    }
    printf("Thread 1 got shared resource\n");
    pthread_mutex_unlock(&lock);
    printf("Thread 1 released lock\n");
    return NULL;
}

void *thread2(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Thread 2 acquired lock\n");
    while (shared_resource == 0) {
        printf("Thread 2 waiting for shared resource\n");
        sleep(1);
    }
    printf("Thread 2 got shared resource\n");
    pthread_mutex_unlock(&lock);
    printf("Thread 2 released lock\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    sleep(2);
    shared_resource = 1;
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}