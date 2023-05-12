#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;
int shared_resource = 0;

void *low_priority_thread(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Low priority thread acquired lock\n");
    while (shared_resource == 0) {
        printf("Low priority thread waiting for shared resource\n");
        // 在低优先级等待的时候尝试放锁 让优先级高的线程访问线程
        pthread_mutex_unlock(&lock);
        sleep(1);
        pthread_mutex_lock(&lock);
    }
    printf("Low priority thread got shared resource\n");
    pthread_mutex_unlock(&lock);
    printf("Low priority thread released lock\n");
    return NULL;
}

void *high_priority_thread(void *arg) {
    pthread_mutex_lock(&lock);
    printf("High priority thread acquired lock\n");
    shared_resource = 1;
    printf("High priority thread set shared resource to 1\n");
    pthread_mutex_unlock(&lock);
    printf("High priority thread released lock\n");
    return NULL;
}

int main() {
    pthread_t low, high;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&low, NULL, low_priority_thread, NULL);
    pthread_create(&high, NULL, high_priority_thread, NULL);
    pthread_join(low, NULL);
    pthread_join(high, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}