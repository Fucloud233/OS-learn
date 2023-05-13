#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define N_THREADS 3
#define N_RESOURCES 2

// 设定资源分配的初始状态
int maxinum[N_THREADS][N_RESOURCES] = {
    {5, 10}, {3, 1}, {10, 11}
}; 
int allocation[N_THREADS][N_RESOURCES] = {
    {2, 8}, {0, 1}, {5, 1}
};
int need[N_THREADS][N_RESOURCES] = {
    {3, 2}, {3, 0}, {5, 10}
};
int available[N_RESOURCES] = {3, 1};

// 银行家算法: 验证线程是否安全
bool isSafe() {
    int work[N_RESOURCES];
    for(int i=0; i<N_RESOURCES; i++)
        work[i] = available[i];

    bool finished[N_THREADS] = {false};

    for(int k=0; k<N_THREADS; k++) {
        // 下面的代码是为了找到第一个能够执行完成的线程
        bool isValid = false;
        for(int i=0; i<N_THREADS; i++) {
            if(finished[k])
                continue;    

            bool can_be_completed = true;

            for(int j=0; j<N_RESOURCES; j++) {
                if(need[i][j]>work[j]) {
                    can_be_completed = false;
                    break;
                }
            }
            
            if(can_be_completed) {
                isValid = finished[k] = true;
                
                for(int j=0; j<N_RESOURCES; j++) 
                    work[j] += allocation[i][j];
                break;
            }
        }

        if(!isValid) {
            return false;
        }
    }

    return true;
}

pthread_mutex_t lock;

void *thread_func(void *arg) {
    long id = (long)arg;

    while(1) {
        pthread_mutex_lock(&lock);

        if(isSafe){
            // 判断当前资源是否能够分配
            bool can_be_allocated = true;
            for(int i=0; i<N_RESOURCES; i++) {
                if(need[id][i] > available[i]) {
                    can_be_allocated = false;
                    break;
                }
            }

            // 如果不能够分配
            if(!can_be_allocated) {
                printf("Thread %li can be not allocated more resources!\n", id);
                pthread_mutex_unlock(&lock);
            }
            // 如果能够分配
            else {
                printf("Thread %li is allocated resources!\n", id);
                printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);

                for(int i=0; i<N_RESOURCES; i++) {
                    available[i] -= need[id][i]; 
                    allocation[id][i] += need[id][i];
                    need[id][i] = 0;
                }

                // 运行代码逻辑..
                sleep(1);

                // 释放资源
                for(int i=0; i<N_RESOURCES; i++) {
                    available[i] += allocation[id][i];
                    allocation[id][i] = 0;
                }

                pthread_mutex_unlock(&lock);
                break;
            }
        }
        else {
            printf("Thread %li is waiting for resources!\n", id);
            pthread_mutex_unlock(&lock);
        }
        
        sleep(1);
    }
}

int main() {
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[N_THREADS];

    for(int i=0; i<N_THREADS; i++) 
        pthread_create(&threads[i], NULL, thread_func, (void *)(long)i);

    for(int i=0; i<N_THREADS; i++) 
        pthread_join(threads[i], NULL);
    
    pthread_mutex_destroy(&lock);
}