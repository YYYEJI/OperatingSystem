#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int sum = 0;
void *runner(void *param);

int main(int argc, char *argv[]) {
    pthread_t tid = 0;
    pthread_attr_t attr;

    if(argc<2) {
        fprintf(stderr, "usage:a.out<integer>\n");
        exit(0);
    }
    if(atoi(argv[1]) < 0) {
        fprintf(stderr, "%d must be <= 0\n", atoi(argv[1]));
        exit(0);
    }

    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* now wait for the thread to exit */
    pthread_join(tid, NULL);
    printf("sum = %d\n", sum);
    return 0;
}   

/* The thread will begin control in this function */
void *runner(void *param) {
    int upper = atoi(param);
    int i = 0; 
    sum = 0;
    if(upper > 0) {
        for(i = 0; i<=upper; i++) {
            sum += i;
        }
    }

    return NULL;
}

/* Execution 
$ gcc 7_thread.c
$ ./a.out 10
*/