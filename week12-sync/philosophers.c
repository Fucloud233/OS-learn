#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

bool is_granted_chopsticks[NUM_PHILOSOPHERS] = { false };

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    // Randomly delay before starting to eat
    usleep(rand() % 1000);

    while (true) {
        // Attempt to acquire both chopsticks
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        pthread_mutex_lock(&chopsticks[right_chopstick]);

        // Mark the chopsticks as granted
        is_granted_chopsticks[left_chopstick] = true;
        is_granted_chopsticks[right_chopstick] = true;

        printf("Philosopher %d is eating using chopsticks %d and %d\n", id, left_chopstick, right_chopstick);

        // Randomly delay before finishing eating
        usleep(rand() % 1000);

        // Mark the chopsticks as released
        is_granted_chopsticks[left_chopstick] = false;
        is_granted_chopsticks[right_chopstick] = false;

        // Release both chopsticks
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);

        printf("Philosopher %d is thinking\n", id);

        // Randomly delay before attempting to eat again
        usleep(rand() % 1000);
    }
    return NULL;
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    return 0;
}