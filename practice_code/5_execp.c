#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wait.h>

int main() {
    pid_t child_pid = fork();      // Create a process

    if (child_pid < 0) {           // Error occurred
        fprintf(stderr, "fork failed\n");
        exit(-1);
    } else if(child_pid == 0) {    // Child process
        execlp("/bin/ls", "ls", NULL);
    } else {                       // Parent process
        wait(NULL); 
        printf("Child Completed\n");
        exit(0);
    }

    return 0;
}