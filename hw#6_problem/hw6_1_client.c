// 5_2_client.c peer review
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("Usage: %s <server-ip> <server-port> <client-port>\n", argv[0]);
		return -1;
	}

	char *server_ip = argv[1];
	int server_port = atoi(argv[2]);

	// TO DO: create a socket
	//  on failure, display an error message and terminate

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0){
		perror("Error creating socket");
		return -1;
	}


	printf("Connecting to %s:%d\n", server_ip, server_port);

	struct sockaddr_in svr_addr = { 0 };
	// TO DO: set svr_addr with appropriate value
	svr_addr.sin_family = AF_INET;                       // IPv4 인터넷 프로토롤
	svr_addr.sin_port = htons(server_port);              // 사용할 서버 포트
	svr_addr.sin_addr.s_addr = inet_addr(server_ip);     // 문자열을 IPv4 주소로 변환
	if(svr_addr.sin_addr.s_addr == INADDR_NONE){         // INADDR_NONE은 -1, 잘못된 값임      
		perror("Error converting server IP address");
		return -1;
	}


	// TO DO: connect to svr_addr using the socket
	//  on failure, display an error message and terminate
	if (connect(client_socket, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) < 0) {
		perror("Failed to connect to server");
		close(client_socket);
		return -1;
	}


	printf("Done.\n");

	/* TO DO: repeat
		read a string from the user
		write the input string to the socket using write()
		read the conversion result from the socket using read()
		display the input string and the conversion result
		if the conversion result is an empty string, break
	*/
	char user_buffer[BUFFER_SIZE];
	char server_buffer[BUFFER_SIZE];

    /*old code
    // 문자열을 server로 보냈을 때 출력 해결해 주세요.
    while (1) {
		memset(server_buffer, 0, sizeof(server_buffer));
		printf("Input a number: ");
		fgets(user_buffer, BUFFER_SIZE, stdin);
		
		user_buffer[strcspn(user_buffer, "\n")] = '\0';      // 문자열에서 일치되는 첫 번째 문자의 위치를 검색
		
		if (strcmp(user_buffer, "quit") == 0) {
			printf("quit ==> \n");
			break;
		}
		
		if (write(client_socket, user_buffer, strlen(user_buffer)) < 0) {
			perror("Failed to send message to server");
			close(client_socket);
			return -1;
		}
		
		if (read(client_socket, server_buffer, BUFFER_SIZE) < 0) {
			perror("Failed to receive message from server");
			close(client_socket);
			return -1;
		}
	
		
		printf("%s ==> %s\n", user_buffer, server_buffer);
	}
    */
    /* new code */

	while (1) {
		memset(server_buffer, 0, sizeof(server_buffer));
		printf("Input a number: ");
		fgets(user_buffer, BUFFER_SIZE, stdin);
		
		user_buffer[strcspn(user_buffer, "\n")] = '\0';      // 문자열에서 일치되는 첫 번째 문자의 위치를 검색
		
		if (strcmp(user_buffer, "quit") == 0) {
			printf("quit ==> \n");
			break;
		}
		
		if (write(client_socket, user_buffer, strlen(user_buffer)) < 0) {
			perror("Failed to send message to server");
			close(client_socket);
			return -1;
		}
		
		if (read(client_socket, server_buffer, BUFFER_SIZE) < 0) {
			perror("Failed to receive message from server");
			close(client_socket);
			return -1;
		}
	
		if(strcmp(server_buffer, " ") == 0) {
			// memset(server_buffer, 0, sizeof(server_buffer));
			break;
		}
		printf("%s ==> %s\n", user_buffer, server_buffer);
	}



	printf("Closing socket\n");

	// TO DO: close the socket
	close(client_socket);



	printf("Done.\n");

	printf("Bye!\n");

	return 0;
}
