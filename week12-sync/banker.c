#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 2
#define NUMBER_OF_RESOURCES 2

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

bool isSafe(int customer_id, int request[]) {
    int work[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS] = { false };
    int i, j, k;

    // Initialize the work vector with available resources
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Allocate the requested resources to the customer and update the work vector
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] -= request[i];
        allocation[customer_id][i] += request[i];
        need[customer_id][i] -= request[i];
    }

    // Find a safe sequence of customers to complete
    for (k = 0; k < NUMBER_OF_CUSTOMERS; k++) {
        for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            if (!finish[i]) {
                int can_be_completed = 1;
                for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_be_completed = 0;
                        break;
                    }
                }
                if (can_be_completed) {
                    finish[i] = true;
                    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    break;
                }
            }
        }
        if (finish[k] == false) {
            // There is no safe sequence of customers to complete
            // We must undo any changes made and return false
            for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
                allocation[customer_id][i] -= request[i];
                need[customer_id][i] += request[i];
            }
            return false;
        }
    }

    // There is a safe sequence of customers to complete
    return true;
}

void printStatus() {
    int i, j;
    printf("Available: ");
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
    printf("Maximum:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("Allocation:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("Need:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i, j;
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = atoi(argv[i + 1]);
    }
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
    printStatus();

    // Request resources from each customer in turn
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        int request[NUMBER_OF_RESOURCES];
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            scanf("%d", &request[j]);
        }
        if (isSafe(i, request)) {
            printf("Request for resources from customer %d granted\n", i);
            printStatus();
        } else {
            printf("Request for resources from customer %d denied\n", i);
        }
    }

    return 0;
}