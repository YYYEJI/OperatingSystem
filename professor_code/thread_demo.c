#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fn(void *arg);

#define NO_THREAD 4

int main()
{
	pthread_t tid[NO_THREAD];
	int index[NO_THREAD] =  { 0 };
	
	int i = 0;
	for(i = 0; i < NO_THREAD; i++){
		index[i] = i;
		pthread_create(&tid[i], NULL, thread_fn, &index[i]);
		// pthread_creat(&tid[i], NULL, thread_fn, &i);
	}	


	for(int i = 0; i < NO_THREAD; i++)
		pthread_join(tid[i], NULL);
	
	printf("Bye!\n");

	return 0;
}

void* thread_fn(void *arg)
{
	int *int_arg = (int*)arg;
	printf("Hello, World!, (idx = %d)\n", *int_arg);

	return NULL;
}
