#include <stdio.h>
#include <unistd.h>

int main() {
    int parent = getpid();
    printf("parent = %d\n", parent);

    fork();
    printf("Hello world!\n");

    return 0;
}