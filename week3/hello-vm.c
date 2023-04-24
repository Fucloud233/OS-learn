#include "stdio.h"

char str[] = "Hello VM!";

int main(void) {
    printf("%s\n", str);
    printf("The (data) address of str is %p.\n", str);
    printf("The (code) address of main is %p.\n", main);
    return 0;
}

