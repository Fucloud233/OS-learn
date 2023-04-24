#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *thread(void *arg) {
    char *ret;
    printf("thread() entered with argument '%s'\n", arg);
    if ((ret = (char*) malloc(20)) == NULL) {
        perror("malloc() error");
        exit(2);
    }
    strcpy(ret, "This is a test");
    pthread_exit(ret);
}

int main() {
    pthread_t thid;
    void *ret;

    if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
        perror("pthread_create() error");
        exit(1);
    }

    // 先正常运行，然后再把下面的pthread_join注释掉，试试看有什么变化
    if (pthread_join(thid, &ret) != 0) {
        perror("pthread_create() error");
        exit(3);
    }

    printf("main thread exited with '%s'\n", ret);
}