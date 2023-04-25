#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int global_resource;

void* thread_inc (void* arg) {
    for (int i = 0; i < 10; i++) {
        global_resource++;
        printf("Increment: %d\n", global_resource);
        sleep(1);
    }
    printf("Thread inc finished.\n");
    return NULL;
}

void* thread_dec (void* arg) {
    for (int i = 0; i < 10; i++) {
        global_resource--;
        printf("Decrement: %d\n", global_resource);
    }
    printf("Thread dec finished.\n");
    return NULL;
}

int main (int argc, char** argv) {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, thread_inc, NULL);
    pthread_create(&threads[1], NULL, thread_dec, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    return EXIT_SUCCESS;
}