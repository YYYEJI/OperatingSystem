/*
	socket_server.c: open a port and converts digit strings into the corresponding alphabet string
		communicates with the client through SOCKET
		e.g., "135246" --> "one three five two four six"

		try to make the output as similar to the following example as possible

	Example) ./socket_server 1234		// server-port = 1234
		port = 1234
		creating socket...
		Done.
		socket binding...
		Done.
		listening socket...
		Done.
		Waiting for connect request...
		Connected.
		input = [1234]					// received "1234" from the client
		output = [one two three four]
		Sending message...				// sending "one two three four" to the client
		Done.
		input = [872]
		output = [eight seven two]
		Sending message...
		Done.
		input = [1004]
		output = [one zero zero four]
		Sending message...
		Done.
		input = [1829401]
		output = [one eight two nine four zero one]
		Sending message...
		Done.
		Closing sockets					// received "quit"
		Done.
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// converts a digit string into the corresponding alphabet string
void Digit2Text(char *digit_string, char *alphabet_str);

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("Usage: %s <server-port>\n", argv[0]);
		return 0;
	}

	int ret = 0;
	int port = atoi(argv[1]);
	printf("port = %d\n", port);

	printf("creating socket...\n");
	// TO DO: create a socket (server socket) using the port number. store the socket in an integer variable
	//	on failure, display an error message and terminate
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        return -1;
    }

	printf("Done.\n");

	struct sockaddr_in svr_addr = { 0 };
	// TO DO: fill svr_addr with appropriate values
	svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(port);
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	printf("socket binding...\n");
	// TO DO: bind the socket to svr_addr
	//	on failure, display an error message and terminate
	ret = bind(server_sock, (struct sockaddr *)&svr_addr, sizeof(svr_addr));
    if (ret < 0) {
        perror("Error binding socket");
        close(server_sock);
        return 1;
    }


	printf("Done.\n");


	printf("listening socket...\n");
	// TO DO: listen the server socket
	//	on failure, display an error message and terminate
	ret = listen(server_sock, 5);
    if (ret < 0) {
        perror("Error listening socket");
        close(server_sock);
        return 1;
    }


	printf("Done.\n");

	struct sockaddr_in client_addr = { 0 };
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_addr_len = 0;

	printf("Waiting for connect request...\n");
	// TO DO: accept a connection request by calling acctp(). keep the client socket in an integer variable
	//	on failure, display an error message and terminate
	int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock < 0) {
        perror("Error accepting");
        close(server_sock);
        return 1;
    }


	printf("Connected.\n");

	char input[64] = "";
	char output[512] = "";

	/* TO DO: repeat
		read an input string from the socket using read()
		if the input is "quit" or an empty string, break
		convert the input into the corresponding alphabet string by calling Digit2Text()
		write the alphabet string into the socket using write()
	*/
	while (1) {
        memset(input, 0, sizeof(input));
        memset(output, 0, sizeof(output));

        ret = read(client_sock, input, sizeof(input));
        if (ret < 0) {
            perror("read");
            break;
        }

        if (strlen(input) == 0 || strcmp(input, "quit\n") == 0) {
            break;
        }

		printf("input = [%s]\n", input);

        Digit2Text(input, output);

        ret = write(client_sock, output, strlen(output));
        if (ret < 0) {
            perror("write");
            break;
        }
		
		if(strcmp(output, " ") == 0) {
			memset(output, 0, sizeof(output));
		}

		printf("output = [%s]\n", output);
		printf("Sending message...\n");
		printf("Done.\n");
    }

	printf("Closing sockets\n");

	// TO DO: close the two sockets
	close(client_sock);
    close(server_sock);

	printf("Done.\n");

	printf("Bye!\n");

	return 0;
}

void Digit2Text(char *digit_str, char *alphabet_str)
{
	static char digit_name[][16] = {
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
	};

	// TO DO: convert a digit string into the corresponding alphabet string
	//	e.g., "135246" --> "one three five two four six"
	// 	if digit_string is an empty string or contains a non-digit character
	//		set alphabet_str to "" and return

	int len = strlen(digit_str);
    int i;

    for (i = 0; i < len; i++) {
        int digit = digit_str[i] - '0';
        strcat(alphabet_str, digit_name[digit]);

		if (!isdigit(digit_str[i])) {
			strcat(alphabet_str, " \0");
			return;
		}
        if (i != len - 1) {
            strcat(alphabet_str, " ");
        } 
    }
}

