#include <stdio.h>

#include <unistd.h>
#include <wait.h>

int main()
{
	int parent = getpid();
	printf("parent = %d\n", parent);


	int child = fork();
	if(child > 0){
		printf("This is the parent, child = %d, pid = %d\n", child, getpid());
		wait(NULL);
	} else if(child == 0) {
		printf("This is the child, child = %d, pid = %d\n", child, getpid());
		execlp("/usr/bin/ls", "ls", "-al", NULL);
	} else {
		printf("Error! Failed to create child process in line %d\n", __LINE__);
	}
//	printf("child = %d, pid = %d\n", child, getpid());

//	int grand_child = fork();
//	printf("grand_child = %d, child = %d, pid = %d\n", grand_child, child, getpid());


	return 0;
}
