#include <stdio.h>

#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"

char* keywords[] = {
	"ls", "mkdir", "touch", "edit", "rm", "help", "clear", "vim"
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

//LE FALTA RECONOCER A NUMEROS
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
		while(isdigit(*str)){
			
			str++;
		}
		
		//operaciones
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
	
		t->lexeme = strdup(str);
		t->type = UNKNOWN;
		return t;					
	}

	free(t);
	return NULL;
}

int main(){
	Token* t = get_next_token("'Ximena Galindo Mata asdfads adsfadsf 1231'");
	print_token(t);
	return 0;
}

