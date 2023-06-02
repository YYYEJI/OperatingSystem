/*
	
	1. Write a text line from the user.
	2. Retrieve the start and end indices of all words from the input text.
	   (a word is a sequence of non-space characters separated by whitespace characters.)
		- Mark the start and end of each word by '[' and ']' in the next line

	ex)
			input a text: Welcome to HGU!   Nice to see you!			// input text
			              [      ][ ][   ]  [   ][ ][  ][   ]			// start and end indices of each words

	Use the isspace() function to decide whether a character is whitespace or not.

	Compile command: gcc hw1_2.c
	
	Execution command: ./a.out

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TEXT 256
bool issapce(char c);

int main()
{
	char *prompt = "input a text: ";
	int prompt_len = strlen(prompt);

	// read a text line
	char text[MAX_TEXT] = "";
	printf("%s", prompt);
	fgets(text, MAX_TEXT, stdin);
	int len = strlen(text) - 1;
	text[len] = 0;
	int check = 1;
	// TO DO: print '[' below the start of each word
	//        print ']' below the space character just after each word
	//		  store each word in the substring array
	//		  - start, end: the start and end indices of the word
	//		  - substr: the word

	printf("              ");     
	for(int i = 0; i<len-1; i++) {          
		if(i == 0 && !isspace(text[i])) printf("[");                     // 첫 번째 문자가 스페이스로 시작하면 '[' 괄호 열고 시작
		 
		if(isspace(text[i]) && isspace(text[i+1])) printf(" ");          // 현재 문자와 다음 문자가 모두 스페이스일 때 ' ' 출력 
		else if(isspace(text[i]) && !isspace(text[i+1])) printf("[");    // 현재 문자는 공백이고, 다음 문자가 문자일 때 '[' 출력
		else if(!isspace(text[i]) && isspace(text[i+1])) printf("]");    // 현재 문자가 문자이고, 다음 문자가 공백일 때 ']' 출력
		else if(!isspace(text[i]) && !isspace(text[i+1])) printf(" ");   // 현재 문자가 문자이고, 다음 문자도 문자일 때 ' ' 출력


		if(i==len-2 && !isspace(text[len-1])) printf("]");               // 마지막 문자가 공백이 아니면 ']' 출력
	}


	putchar('\n');
	printf("Bye!\n");

	return 0;
}

bool issapce(char c) {
	if (c == ' ') return true;
	return false;
}