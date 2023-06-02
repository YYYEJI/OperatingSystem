#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fn(void *arg);
#define NO_THREAD 4

int main() {
    pthread_t tid[NO_THREAD];

    for(int i = 0; i<NO_THREAD; i++) {
        pthread_create(&tid[i], NULL, thread_fn, NULL);
    }

    for(int i = 0; i<NO_THREAD; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Bye!");
    return 0;
}

void* thread_fn(void *arg) {
    printf("Hello, World!, (idx = %d)\n", (int)arg);
    return NULL;
}


/* output
!WARNING

Hello, World!, (ind = 1)
Hello, World!, (ind = 0)
Hello, World!, (ind = 2)
Hello, World!, (ind = 3)
Bye! 

// thread의 순서는 실행될 때마다 달라질 수 있음 -> 병렬처리
*/