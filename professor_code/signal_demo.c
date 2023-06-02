#include <stdio.h>

#include <unistd.h>
#include <signal.h>

void handler(int arg);

int main() {
    int i = 0;
    
    signal(SIGINT, handler);

    while(1) {
        print("i = %d\n", i++);
        sleep(1);
    }
}

void handler(int arg) {
    printf("running handler(%d)\n", arg);
}

// control+\ (if you want to kill)


