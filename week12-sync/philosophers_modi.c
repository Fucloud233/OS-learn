#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5
#define N_RESOURCES 5

pthread_mutex_t lock;

pthread_t philosophers[NUM_PHILOSOPHERS];

int allocation[NUM_PHILOSOPHERS][N_RESOURCES] = {
    {0}, {0}, {0}, {0}, {0}
};

int need[NUM_PHILOSOPHERS][N_RESOURCES] = {
    {0}, {0}, {0}, {0}, {0}
};

int available[NUM_PHILOSOPHERS];

// 银行家算法: 验证线程是否安全
bool isSafe() {
    int work[N_RESOURCES];
    for(int i=0; i<N_RESOURCES; i++)
        work[i] = available[i];

    bool finished[NUM_PHILOSOPHERS] = {false};

    for(int k=0; k<NUM_PHILOSOPHERS; k++) {
        // 下面的代码是为了找到第一个能够执行完成的线程
        bool isValid = false;
        for(int i=0; i<NUM_PHILOSOPHERS; i++) {
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

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // while (true) {
    for(int k=0; k<5; k++) {
        // 循环处理 知道用餐完毕
        while(true) {
            // 1. 申请资源
            pthread_mutex_lock(&lock);
            need[id][left] = need[id][right] = 1;

            // 2. 根据银行家算法 判断是否安全
            if(isSafe()) {
                if(available[left] < need[id][left] || available[right] < need[id][right]) {
                    printf("Philosopher %d can't use chopstick\n", id);
                    pthread_mutex_unlock(&lock);
                }
                else {
                    printf("Philosopher %d is using chopstick\n", id);
                    
                    // 3. 使用资源
                    available[left] -= need[id][left];
                    available[right] -= need[id][right];
                    allocation[id][left] += need[id][left];
                    allocation[id][right] += need[id][right];
                    need[id][left] = need[id][right] = 0;

                    pthread_mutex_unlock(&lock);

                    // 4. 处理业务
                    sleep(1);

                    // 5. 释放资源      
                    pthread_mutex_lock(&lock);  

                    printf("Philosopher %d isn't using chopstick\n", id);

                    available[left] += allocation[id][left];
                    available[right] += allocation[id][right];
                    allocation[id][left] = allocation[id][right] = 0;

                    pthread_mutex_unlock(&lock);
                    break;
                }
            }
            else {
                // 2a. 申请不到 则放弃资源
                need[id][left] = need[id][right] = 0;
                printf("Philosopher %d is waiting for chopsticks\n", id);
                pthread_mutex_unlock(&lock);
            }
            
            sleep(1);
        }

        // 一个线程占用一次后 需要等待
        sleep(1.5);
    }

    return NULL;
}

int main() {
    // 分配初始资源
    for(int i=0; i<NUM_PHILOSOPHERS; i++) 
        available[i] = 1;
    pthread_mutex_init(&lock, NULL);


    int i;
    int ids[NUM_PHILOSOPHERS];
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}