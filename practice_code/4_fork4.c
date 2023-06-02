#include <stdio.h>
#include <unistd.h>

int main() {
    int parent = getpid();              // 2^0
    printf("parent = %d\n", parent);

    int child = fork();                 // 2^1
    printf("child = %d, pid = %d\n", child, getpid());
  
    int grand_child = fork();           // 2^2
    printf("grand_child = %d, child = %d, pid = %d\n", grand_child, child, getpid());

    int grand_grand_child = fork();     // 2^3
    printf("grand_grand_child = %d, grand_child = %d, child = %d, pid = %d\n", grand_grand_child, grand_child, child, getpid());
    
    return 0;
}