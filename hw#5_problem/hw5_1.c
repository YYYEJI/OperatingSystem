// Updated solution to midterm 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	_DEBUG				// do not disable this macro

#define TRUE 1
#define FALSE 0

#define P2C 0				// parent to child
#define C2P 1				// child to parent

#define MAX_LEN 128

typedef struct {
	int is_loaded;			// is_loaded == TRUE indicates a data is loaded in buffer. otherwise, buffer is not ready
	char buffer[MAX_LEN];	// buffer to store the data
} SharedBuffer;

/*
	Transferring data through SharedBuffer

	sender:
		wait until is_loaded becomes FALSE
		store data in buffer
		set is_loaded to TRUE
		
	receiver:
		wait until is_loaded becomes TRUE
		retrieve data from buffer
		set is_loaded to FALSE

*/


void* Parent(void *arg);
void* Child(void *arg);
int Evaluate(char *expression);

int main(int argc, char *argv[])
{
	// TO DO: allocate an array composed of two SharedBuffer instances in a shared memory block
	//		the size of shared memory block should be sizeof(SharedBuffer) * 2.
	// 		one is for data transfer from the parent to the child.
	// 		the other is for data transfer from the child to the parent.
	//		call shmget() and shmat()
	// 		on failure, display an error message, deallocate the shared memory block if necessary, and quit.
	// 		otherwise, display the id of the shared memory block for debug.
	int shmid;
    SharedBuffer *shm_buffer;

	shmid = shmget(IPC_PRIVATE, sizeof(SharedBuffer) * 2, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    printf("shmid = %d\n", shmid);

    shm_buffer = (SharedBuffer*)shmat(shmid, NULL, 0);
    if (shm_buffer == NULL) {
        perror("shmat failed");
        shmctl(shmid, IPC_RMID, NULL);
        exit(1);
    }


	// initialize shm_buffer[0] and shm_buffer[1] (set the is_loaded fields to FALSE and the buffer fields to an empty string.)
	shm_buffer[P2C].is_loaded = FALSE;
	shm_buffer[P2C].buffer[0] = 0;
	shm_buffer[C2P].is_loaded = FALSE;
	shm_buffer[C2P].buffer[0] = 0;

	// TO DO: create a child process
	// 		on failure, display an error message, detatch and deallocate the shared memory block, and terminate.
	//		In the child process,
	//			call the Child() function passing the address to the SharedBuffer array.
	//			detatch the shared memory block
	//			call exit(0) for safety
	// 		In the parent process,
	//			call the Parent() function passing the address to the SharedBuffer array.
	//			detatch and destroy the shared memory block

	pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        shmdt(shm_buffer);
        shmctl(shmid, IPC_RMID, NULL);
        exit(1);
    }

    if (pid == 0) { 
        Child(shm_buffer);
        shmdt(shm_buffer);
        exit(0);
    } else { 
        Parent(shm_buffer);
        shmdt(shm_buffer);
        shmctl(shmid, IPC_RMID, NULL);
    }


	system("ipcs");		// run 'icps' to check if the shared memory block was correctly deallocated
						// if your VM does not have icps, install it by running 'sudo apt install util-linux'
	printf("Bye!\n");

	return 0;
}

void* Parent(void *arg)
// TO DO: implement this function
// 		read integer expressions from the user
// 		send the expression to the child process through the shareed memory buffer
//		receive the result from the child through the shared memory buffer
//		display the expression and result
{
	SharedBuffer *shm_buffer = (SharedBuffer *)arg;

	// Algorithm)
	//	repeat until the user types "quit"
	// 		read an integer expression as a string (e.g., "5+3", "7 * 5", etc.) - use fgets()
	// 		if the input is not an empty string,
	// 			send the expression to the child through shm_buffer[P2C]
	// 				wait until the is_loaded field is FALSE
	//				copy the expression into the buffer field
	//				set the is_loaded field to TRUE
	// 			if the input string is "quit", break the loop
	// 			receive the result of the expression from the child through shm_buffer[C2P]
	//				wait until the is_loaded field is TRUE
	//				copy the result from the buffer field
	//				set the is_loaded field to FALSE
	// 			display the expression and the result from the child.
	//	display a message indicating that the parent is terminating.


    // previous code
    /*  child의 마지막 종료문이 출력되지 않습니다.
    while (1) {
		printf("[parent] Input an integer binary expressions(type \"quit\" to finish.): ");
		fgets(expression, MAX_LEN, stdin);
		expression[strcspn(expression, "\n")] = 0;	

		if (strlen(expression) > 0) {
			if (strcmp(expression, "quit") == 0) break;
			

			while (shm_buffer[P2C].is_loaded == TRUE) {	
				sleep(0);
			}
			strcpy(shm_buffer[P2C].buffer, expression);
			shm_buffer[P2C].is_loaded = TRUE;


			while (shm_buffer[C2P].is_loaded == FALSE) {	
				sleep(0);
			}
			strcpy(result, shm_buffer[C2P].buffer);
			shm_buffer[C2P].is_loaded = FALSE;

			printf("[parent] %s = %s\n", expression, result);
		}
	}
	printf("[parent] Terminating Parent.\n");
    */

	char expression[MAX_LEN] = "";
	char result[MAX_LEN] = "";

	while (1) {
		printf("[parent] Input an integer binary expressions(type \"quit\" to finish.): ");
		fgets(expression, MAX_LEN, stdin);
		expression[strcspn(expression, "\n")] = 0;	

		if (strlen(expression) > 0) {
			while (shm_buffer[P2C].is_loaded == TRUE) {	
				sleep(0);
			}
			strcpy(shm_buffer[P2C].buffer, expression);
			shm_buffer[P2C].is_loaded = TRUE;

            if (strcmp(expression, "quit") == 0) break;
            
			while (shm_buffer[C2P].is_loaded == FALSE) {	
				sleep(0);
			}

			strcpy(result, shm_buffer[C2P].buffer);
			shm_buffer[C2P].is_loaded = FALSE;
			printf("[parent] %s = %s\n", expression, result);
		}
	}
	sleep(0);
	printf("[parent] Terminating Parent.\n");
}

void* Child(void *arg)
// TO DO: implement this function
// 		receive an integer expressions from the parent by message passing
//		compute the result of the expression
// 		send the result to the parent process by message passing
{
	SharedBuffer *shm_buffer = (SharedBuffer *)arg;

	// Algorithm)
	// 	repeat until the incomming message is "quit"
	// 		receieve an expression from the parent through the message queue p2c.
	// 			on failure, display an error message.
	// 		for debug, display the incoming message, its index, and the return value of msgrcv().
	// 		if the message is "quit", break the loop
	// 		compute the evaluation in the incoming message
	// 		for debug, display the outgoing message and its index.
	// 		send the result as a string to the parent through the message queue c2p.
	// 			on failure, display an error message.
	//		for debug, display the return value of msgsnd().
	// 		increase the index of outgoing message.
	//
	//	display a message indicating that the child is terminating.

	char expression[MAX_LEN] = "";
	char result[MAX_LEN] = "";
	
	while (1) {
		while (shm_buffer[P2C].is_loaded == FALSE) {	
			sleep(0);
		}
		strcpy(expression, shm_buffer[P2C].buffer);
		shm_buffer[P2C].is_loaded = FALSE;
		printf("[child] received expression \"%s\"\n", expression);

		if (strcmp(expression, "quit") == 0) break;

		int evaluation = Evaluate(expression);
		sprintf(result, "%d", evaluation);

		while (shm_buffer[C2P].is_loaded == TRUE) {	
			sleep(0);
		}
		strcpy(shm_buffer[C2P].buffer, result);
		shm_buffer[C2P].is_loaded = TRUE;

		printf("[child] sending result \"%s\"\n", result);
	}

	sleep(0.5);
	printf("[child] Terminating Child.\n");
}


int Evaluate(char *expression)
{
	int op1 = 0, op2 = 0;
	char op = 0;
	int result = 0;

	int ret = sscanf(expression, "%d %c %d", &op1, &op, &op2);
	if(ret == 3){
		switch(op){
		case '+':
			result = op1 + op2;
			break;

		case '-':
			result = op1 - op2;
			break;

		case '*':
			result = op1 * op2;
			break;

		case '/':
			if(op2 != 0)
				result = op1 / op2;
			break;
		}
	}

	return result;
}

