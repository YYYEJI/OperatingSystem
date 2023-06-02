#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int sum = 0;
void *runner(void *param);

int main(int argc, char *argv[]) {
    int NUM_THREADS = argc-1;
    int i = 0, policy = 0;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if(argc<2) {
        fprintf(stderr, "usage:a.out<integer>\n");
        exit(0);
    }
    if(atoi(argv[1]) < 0) {
        fprintf(stderr, "%d must be <= 0\n", atoi(argv[1]));
        exit(0);
    }

    if(pthread_attr_getschedpolicy(&attr, &policy)!=0) 
        fprintf(stderr, "Unable to get policy.\n");
    else {
        if(policy == SCHED_OTHER) printf("SCHED OTHER\n");
        else if(policy == SCHED_RR) printf("SCHED RR\n");
        else if(policy == SCHED_FIFO) printf("SCHED FIFO\n");
    }

    if(pthread_attr_setschedpolicy(&attr, SCHED_FIFO)!=0)
        fprintf(stderr, "Unable to set policy.\n");

    for(i = 0; i< NUM_THREADS; i++) 
        pthread_create(&tid[i], &attr, runner, argv[i+1]);

    for(i = 0; i< NUM_THREADS; i++)
        pthread_join(tid[i], NULL);

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