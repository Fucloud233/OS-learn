#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// 资源的种类数量
#define N_RESOURCES 3
#define N_THREADS 2

int available[N_RESOURCES];

int maxinum[N_THREADS][N_RESOURCES] = {
    {3, 1, 2}, {1, 3, 1}
};

int allocation[N_THREADS][N_RESOURCES] = {
    {0, 1, 0}, {1, 0, 0}
};

int need[N_THREADS][N_RESOURCES] = {
    {3, 0, 2}, {0, 3, 1}
};

bool isSafe() {
    bool finish[N_THREADS] = { false };

    // 1. 创建1个临时数组
    int work[N_RESOURCES];
    for(int i=0; i<N_RESOURCES; i++)
        work[i] = available[i];
    
    // 2. 外层循环控制所有线程都能够运行完成
    for(int k=0; k<N_THREADS; k++) {


        // 3. 判断哪个线程能够运行完成
        bool is_valid = false;
        
        for (int i=0; i<N_THREADS; i++) {
            // 如果结束了 就跳过
            if(finish[i]) {
                continue;
            }

            // 循环判断: whether 需要的>可用的  
            bool can_be_completed = true;
            for(int j=0; j<N_RESOURCES; j++) {
                if(need[i][j] > work[j]) {
                    can_be_completed = false;
                    break;
                }
            }

            // 如果能被完成
            if(can_be_completed) {
                is_valid = true;
                finish[i] = true;

                // 且该线程完成之后 可以提供更多的内存空间
                for(int j=0; j<N_RESOURCES; j++)
                    work[j] += allocation[i][j];
                break;
            }
        }  
        
        // 两个线程都不行
        if(is_valid == false) 
            return false;       
    }

    return true;
}

// 使用1个B类资源
void *thread1(void* arg) {
    int request[N_RESOURCES] = {0, 1, 0};
    pthread_mutex_t *lock = (pthread_mutex_t *) arg;

    while(1) {
        // 判断的拿锁是否成功
        pthread_mutex_lock(lock);

        if(isSafe()) {
            if(need[0][1]<1) 
                printf("Thread 1 can not allocated more resources\n");
            else {
                printf("Thread 1 allocated resources\n");
                printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);

                allocation[0][1]++;
                need[0][1]--;
                available[1]--;
            }
            
            pthread_mutex_unlock(lock);
            sleep(1);
        }
        else {
            printf("Thread 1 waiting for resources\n");
            pthread_mutex_unlock(lock);
            sleep(1);
        }
    }

    return NULL;
}

// 使用2个A类资源
void *thread2(void *arg) {
    int request[N_RESOURCES] = {2, 0, 0};
    pthread_mutex_t *lock = (pthread_mutex_t *) arg;

    while(1) {
        // 判断的拿锁是否成功
        pthread_mutex_lock(lock);

        if(isSafe()) {
            if(need[1][0]<2) 
                printf("Thread 1 can not allocated more resources\n");
            else {
                printf("Thread 1 allocated resources\n");
                printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);

                allocation[1][0] += 2;
                need[1][0] -= 2;
                available[0] -= 2;
            }
            
            pthread_mutex_unlock(lock);
            sleep(1);
        }
        else {
            printf("Thread 1 waiting for resources\n");
            pthread_mutex_unlock(lock);
            sleep(1);
        }
    }

    return NULL;
}


int main() {
    pthread_t threads[N_THREADS];
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    for(int i=0; i< N_RESOURCES; i++) 
        available[i] = 8;
    
    pthread_create(&threads[0], NULL, thread1, (void*)&lock);
    pthread_create(&threads[1], NULL, thread2, (void*)&lock);

    for(int i=0; i<2; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
}