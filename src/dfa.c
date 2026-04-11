#include <stdio.h>

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/token.h"


char* keywords[] = {
	"ls", "mkdir", "touch", "edit", "rm", "help", "clear", "vim"
};

int is_keyword(const char* str) {
	if(!str) return -1;
	int num_keywords = sizeof(keywords)/sizeof(keywords[0]);
	for(int i = 0; i < num_keywords; i++){
		int flag = strcmp(str, keywords[i]);
		if(flag == 0) return 1;
	}
	return 0;
}

Token* get_next_token(const char* input) {
	Token* t;
	const char* srt = input;
	return t;
}

int main(){
	printf("hola mundo\n");
	printf("%i\n", is_keyword("mkdir"));
	return 0;
}
