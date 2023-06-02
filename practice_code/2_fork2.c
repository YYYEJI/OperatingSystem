#include <stdio.h>
#include <unistd.h>

int main() {
    int parent = getpid();
    printf("parent = %d\n", parent);

    int child = fork();
    printf("child = %d, pid = %d\n", child, getpid());

    return 0;
}