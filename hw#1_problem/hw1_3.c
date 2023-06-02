/*
	
	1. Write a text line from the user.
	2. Retrieve all words from the input text.
	   (a word is a sequence of non-space characters separated by whitespace characters.)
		- Mark the start and end of each word by '[' and ']' in the next line.
		- Store all words in an array of structures 'words'.
	3. Display all words in the array 'words'.

	ex)
			input a text: Welcome to HGU!   Nice to see you!			// input text
			              [      ][ ][   ]  [   ][ ][  ][   ]			// start and end indices of each words

			words[0] = (0, 7, Welcome)
            words[1] = (8, 10, to)
            words[2] = (11, 15, HGU!)
            words[3] = (18, 22, Nice)
            words[4] = (23, 25, to)
            words[5] = (26, 29, see)
            words[6] = (30, 34, you!)


	Use the isspace() function to decide whether a character is whitespace or not.

	Compile command: gcc hw1_3.c
	
	Execution command: ./a.out

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define MAX_TEXT 256
#define MAX_LEN 128
#define SIZE 512

bool issapce(char c);



typedef struct {
	int start, end;			// the start and end indices of the word
	char substr[MAX_LEN];	// substring (word)
} Substring;

Substring words[SIZE];	 	// array of structures to store words
int no_word = 0;			// the number of words


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

	// TO DO: print '[' below the start of each word
	//        print ']' below the space character just after each word
	//		  store each word in the substring array
	//		  - start, end: the start and end indices of the word
	//		  - substr: the word



	printf("              ");     
	for(int i = 0; i<len-1; i++) {          
		if(i == 0 && !isspace(text[i])) printf("[");                  
		 
		if(isspace(text[i]) && isspace(text[i+1])) printf(" ");         
		else if(isspace(text[i]) && !isspace(text[i+1])) printf("[");   
		else if(!isspace(text[i]) && isspace(text[i+1])) printf("]");    
		else if(!isspace(text[i]) && !isspace(text[i+1])) printf(" ");   

		if(i==len-2 && !isspace(text[len-1])) printf("]");               
	}

	char * s = (char*)malloc(sizeof(char)*8);
	int index = 0;
	int start_i = 0;
	int str_i = 0;

	for(int i = 0; i<len; i++) {
		if(text[i]!=' ' && i!=len-1) {
			s[str_i] = text[i];
			str_i++;
			index++;
			if(i==len-2 && text[len-1]!=' ') {
				s[str_i] = text[i+1];
				index++;
			}
		}
		else if((text[i]==' ' && text[i+1]!=' ') || (i==len-1 && text[len-1]!=' ')) {
			str_i = 0;
			
			// printf("\n%d %d %s", start_i, start_i+index, s);     
			words[no_word].start = start_i;
			words[no_word].end = start_i+index;
			strcpy(words[no_word].substr, s);

			start_i = i + 1;
			
			int interval = index + 1;
			s = (char*)malloc(sizeof(char)*interval);
			index = 0;

			no_word++;
		}

	}


	

	// DO NOT modify the following four lines
	putchar('\n');
	putchar('\n');
	for(int i = 0; i < no_word; i++)
		printf("words[%d] = (%d, %d, %s)\n", i, words[i].start, words[i].end, words[i].substr);

	printf("Bye!\n");

	free(s);


	return 0;
}

bool issapce(char c) {
	if (c == ' ') return true;
	return false;
}

