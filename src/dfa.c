#include <stdio.h>

#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"
#include "../include/list.h"


char* keywords[] = {
  "ls", "mkdir", "touch", "edit", "rm", "help", "clear", "vim", "echo"
};

char operations[] = {
	'-', '*', '/', '+'
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

int is_operation(const char str){
	return(str == operations[0] || str == operations[1] || str == operations[2] || str == operations[3]);
}

Token* get_next_token(const char* input) {
	if(!input) return NULL;
	Token* t = init_token();
	if(!t) return NULL;
	const char* str = input;
	//alfabetos
	if(isalpha(*str)){
		if(is_keyword(str)){
			t->lexeme = strdup(str);
			t->type = KEYWORD;
			return t;
		}else{
			const char *aux = str;
			while(*aux){
				if(!isalpha(*aux) && !isdigit(*aux)){
					t->lexeme = strdup(str);
					t->type = UNKNOWN;
					return t;	
				}
				aux++;
			}
			t->lexeme = strdup(str);
			t->type = VARIABLE;
			return t;
		}
		//numeros
	}else if(isdigit(*str)){
		while(*str != 0){
			if(!isdigit(*str) && *str != 0){
				t->lexeme = strdup(str);
				t->type = UNKNOWN;
				return t;									}
			str++;
		}
		t->lexeme = strdup(input);
		t->type = NUMBER;
		return t;			
	}if(is_operation(*str)){
		if(strlen(str) == 1){
			t->lexeme = strdup(str);
			t->type = OPERATION;
			return t;			
		}else{
			t->lexeme = strdup(str);
			t->type = UNKNOWN;
			return t;			
		}
		//cadenas
	}else if(*str == 39){
		str++;
		while(*str != EOF){
			str++;
			if(*str == 39){
				printf("es una cadena \n");
				t->type = STRING;
				t->lexeme = strdup(input);
				return t; 				
			}
		}
		
		printf("no se encontro una cadena\n");
		t->lexeme = strdup(str);
		t->type = UNKNOWN;
		return t;
		

		//errores
	}else{
		printf("esto es un error no deberias estar aqui!\n");
		t->lexeme = strdup(str);
		t->type = UNKNOWN;
		return t;					
	}

	free(t);
	return NULL;
}
 
void clean_buffer(char buffer[1000]){
	for(int i = 0; i < 1000; i++){
		buffer[i] = 0;
	}
}

List* tokenize(const char* input){
	if(!input) return NULL;

	List* l = init_list();
	if(!l) return NULL;
 
	const char* str = input;

	char buffer[1000];
	int i = 0;
  
	while(1){
		if(*str == 32) {
			buffer[i] = '\0';
			Token* t = get_next_token(buffer);
			push_token(l,t);
			str++;
			i= 0;
			clean_buffer(buffer);
		}
		if(*str == 0){
			Token* t = get_next_token(buffer);
			push_token(l,t);
			i = 0;
			return l;
		}
		buffer[i] = *str;
		str++;
		i++;
	}
	return NULL;
}


  
int main(){
	Token* t = get_next_token("'gaspar es puto'");
	//List* l = tokenize("gaspar + 1 'como estas'");
	//	print_list(l);
	print_token(t);
	return 0;
}

