#include <stdbool.h>

#define N_RESOURCES 3
#define N_THREADS 2

int maxinum[N_THREADS][N_RESOURCES];
int allocation[N_THREADS][N_RESOURCES];
int need[N_THREADS][N_RESOURCES];

int available[N_RESOURCES];

bool isSafe() {
    // 1. 初始化个临时数组
    int work[N_THREADS];
    for(int i=0; i<N_THREADS; i++) 
        work[i] = available[i];

    // 2. 验证是是否线程能够满足条件
    bool is_valid = false;

    for(int i=0; i<N_THREADS; i++) {
        bool can_complete = true;
        for(int j=0; j<N_THREADS; j++) {
            if(need[i][j]<work[j]) {
                can_complete = false;
                break;
            }
        }

        if(can_complete) 
            is_valid = true;
    }

    //3. 

    return is_valid;    
}