#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// compiler command: gcc --static -o vm-example.o vm-example.c
// run: ./vm-example 1 & ./vm-example 2 & wait

int g_val = 0;

int main(int argc, char** argv) {
    g_val = strtol(argv[1], NULL, 10);

    for(int i = 0; i < 2; i++) {
        printf("The address of g_val is %p.\n", &g_val);
        printf("The value   of g_val is %d.\n", g_val);
        sleep(1);
    }
}