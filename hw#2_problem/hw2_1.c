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

    // previous code
    /* <old code> 
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
    */
	

    // updated code<new code>
    printf("             ");     
    //여는 괄호 부분의 인덱스가 정확하지 않은 것 같습니다.
	for(int i = 0; i<len-1; i++) {          
		if(i == 0 && !isspace(text[i])) printf(" [");                  
		 
		if(isspace(text[i]) && isspace(text[i+1])) printf(" ");         
		else if(isspace(text[i]) && !isspace(text[i+1])) printf("[");   
		else if(!isspace(text[i]) && isspace(text[i+1])) printf("]");    
		else if(!isspace(text[i]) && !isspace(text[i+1])) printf(" ");   

		if(i==len-2 && !isspace(text[len-1])) printf("]");               
	}

    //시작 단어의 길이가 8을 초과할 경우 malloc되지 않은 공간의 값이 추후 변경될 우려가 있을 것 같습니다. 
	char * s = (char*)malloc(sizeof(char)*MAX_LEN);
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

