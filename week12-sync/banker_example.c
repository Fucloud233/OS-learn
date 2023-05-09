#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define NUMBER_OF_RESOURCES 3
int available[NUMBER_OF_RESOURCES];

int maximum[2][NUMBER_OF_RESOURCES] = {
    {3, 1, 2},
    {1, 3, 1}};

int allocation[2][NUMBER_OF_RESOURCES] = {
    {0, 1, 0},
    {1, 0, 0}};

int need[2][NUMBER_OF_RESOURCES] = {
    {3, 0, 2},
    {0, 3, 1}};
bool isSafe()
{
    int work[NUMBER_OF_RESOURCES];
    int finish[2] = {false};
    int i, j, k;

    // Initialize the work vector with available resources
    for (i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    // Find a safe sequence of threads to complete
    for (k = 0; k < 2; k++)
    {
        bool is_valid = false;
        for (i = 0; i < 2; i++)
        {
            if (!finish[i])
            {
                int can_be_completed = 1;
                for (j = 0; j < NUMBER_OF_RESOURCES; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        can_be_completed = 0;
                        break;
                    }
                }
                if (can_be_completed)
                {
                    is_valid = true;
                    finish[i] = true;
                    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    break;
                }
            }
        }
        if (is_valid == false)
        {
            // There is no safe sequence of threads to complete
            return false;
        }
    }

    // There is a safe sequence of threads to complete
    return true;
}

void *thread1(void *arg)
{
    int request[NUMBER_OF_RESOURCES] = {0, 1, 0};
    pthread_mutex_t *lock = (pthread_mutex_t *)arg;
    while (1)
    {
        if (pthread_mutex_lock(lock) != 0)
        {
            printf("Error acquiring lock\n");
            return NULL;
        }
        if (isSafe())
        {
            if (need[0][1] < 1)
            {
                printf("Thread 1 can not allocated more resources\n");
            }
            else
            {
                printf("Thread 1 allocated resources\n");
                printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);
                allocation[0][1]++;
                need[0][1]--;
                available[1]--;
            }

            if (pthread_mutex_unlock(lock) != 0)
            {
                printf("Error releasing lock\n");
                return NULL;
            }
            sleep(1);
        }
        else
        {
            printf("Thread 1 waiting for resources\n");
            if (pthread_mutex_unlock(lock) != 0)
            {
                printf("Error releasing lock\n");
                return NULL;
            }
            sleep(1);
        }
    }
    return NULL;
}

void *thread2(void *arg)
{
    int request[NUMBER_OF_RESOURCES] = {2, 0, 0};
    pthread_mutex_t *lock = (pthread_mutex_t *)arg;
    while (1)
    {
        if (pthread_mutex_lock(lock) != 0)
        {
            printf("Error acquiring lock\n");
            return NULL;
        }
        if (isSafe())
        {
            if (need[1][0] < 2)
            {
                printf("Thread 2 can not allocated more resources\n");
            }
            else
            {
                printf("Thread 2 allocated resources\n");
                printf("Available resources: %d %d %d\n", available[0], available[1], available[2]);
                allocation[1][0] += 2;
                need[1][0] -= 2;
                available[0] -= 2;
            }

            if (pthread_mutex_unlock(lock) != 0)
            {
                printf("Error releasing lock\n");
                return NULL;
            }
            sleep(1);
        }
        else
        {
            printf("Thread 2 waiting for resources\n");
            if (pthread_mutex_unlock(lock) != 0)
            {
                printf("Error releasing lock\n");
                return NULL;
            }
            sleep(1);
        }
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    int i;
    for (i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] = 8;
    }
    pthread_create(&t1, NULL, thread1, (void *)&lock);
    pthread_create(&t2, NULL, thread2, (void *)&lock);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
}