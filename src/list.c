#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

struct List{
	Token* head;
};

//METODOS DE IMPLEMENTACION, NO DE LA API
Token* init_token();
List* init_list();
int push_token(List** l, Token* t);
void destoy_list(List **l);

//METODOS DE DEBUG
void print_token(Token* t){
	printf("current token:%p\n", t);
	printf("next:%p\n", t->next);
	printf("lexeme:%s\n", t->lexeme);
	printf("type:%i\n", t->type);
}

void print_list(List* l){
	Token* aux = l->head;
	while(aux){
		print_token(aux);
		aux = aux->next;
	}
	return;
}

//COMIENZO DEL PROGRAMA
int main(){
	List* l = init_list();
	Token* t = init_token();
	Token* t2 = init_token();
	printf("%i",push_token(&l, t) );
	printf("%i",push_token(&l, t2) );
	printf("\n");
	print_list(l);
	return 0;
}

//DEFINICION DE METODOS NECESARIOS
Token* init_token(){
	Token* t;
	t = malloc(sizeof(Token));
	if(!t) return NULL;
	t->next = NULL;
	t->lexeme = NULL;
	t->type = UNKNOWN;
	return t;
}

List* init_list(){
	List *l;
	l = malloc(sizeof(List));
	if(!l) return NULL;
	l->head = NULL;
	return l;
}

int push_token(List** l, Token *t){
	if(!*l || !t) return -1;

	if(!(*l)->head){
		(*l)->head = t;
		return 0;
	}else{
		Token* aux = (*l)->head;
		while(aux->next){
			aux = aux->next;
		}
		aux->next = t;
		return 0;
	}
	return -1;
}

void destoy_list(List **l){
	
}
