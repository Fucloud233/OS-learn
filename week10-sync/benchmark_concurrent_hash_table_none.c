#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TABLE_SIZE 10007 // size of the hash table
#define N_OPERATIONS 10000000 // total number of operations to perform
#define N_THREADS 10 // number of threads to use
#define READ_RATIO 0.8 // ratio of read operations (rest are write and delete)


typedef struct node {
    int key;
    int value;
    struct node* next;
} node_t;

node_t* table[TABLE_SIZE]; // array of linked lists, one for each hash bucket

void hash_init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}

void hash_insert(int key, int value) {
    int index = key % TABLE_SIZE;
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next = table[index];
    table[index] = new_node;
}

int hash_search(int key) {
    int index = key % TABLE_SIZE;
    node_t* current = table[index];
    while (current != NULL) {
        if (current->key == key) {
            int value = current->value;
            return value;
        }
        current = current->next;
    }
    return -1; // key not found
}

void hash_delete(int key) {
    int index = key % TABLE_SIZE;
    node_t* current = table[index];
    node_t* previous = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (previous == NULL) {
                table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}


void* worker(void* arg) {
    srand(time(NULL) + (long)arg); // seed random number generator
    int n_reads = 0, n_writes = 0, n_deletes = 0;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time); // start timer

    for (int i = 0; i < N_OPERATIONS / N_THREADS; i++) {
        double p = (double)rand() / RAND_MAX;
        if (p < READ_RATIO) {
            int key = rand() % N_OPERATIONS; // assume keys are integers in [0, N_OPERATIONS)
            hash_search(key);
            n_reads++;
        } else if (p < 0.9) {
            int key = rand() % N_OPERATIONS;
            int value = rand() % 1000; // assume values are integers in [0, 1000)
            hash_insert(key, value);
            n_writes++;
        } else {
            int key = rand() % N_OPERATIONS;
            hash_delete(key);
            n_deletes++;
        }
    }

    clock_gettime(CLOCK_REALTIME, &end_time); // end timer
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 1e-9 * (end_time.tv_nsec - start_time.tv_nsec);
    printf("Thread %ld finished: %.0f reads/sec, %.0f writes/sec, %.0f deletes/sec\n", (long)arg, n_reads / elapsed_time, n_writes / elapsed_time, n_deletes / elapsed_time);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N_THREADS];

    hash_init();

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time); // start timer

    for (int i = 0; i < N_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)(long)i);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_REALTIME, &end_time); // end timer
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 1e-9 * (end_time.tv_nsec - start_time.tv_nsec);
    printf("Benchmark finished in %f seconds\n", elapsed_time);

    return 0;
}
