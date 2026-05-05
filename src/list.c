#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"


List* init_list();
int push_token(List* l, Token* t);
void destoy_list(List **l);

void print_list(List* l){
	if(!l) return;
	Token* aux = l->head;

	printf("head: %p\n", l->head);
	printf("tail: %p\n", l->tail);
	printf("========\n");
	while(aux){

		print_token(aux);
	printf("\n");

		aux = aux->next;
	}
	return;
}

List* init_list(){
	List *l;
	l = malloc(sizeof(List));
	if(!l) return NULL;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

int push_token(List* l, Token *t){
	if(!l || !t) return -1;
	if(!l->head){
		l->head = t;
		l->tail = l->head;
		return 0;
	}else{
		Token* aux = l->tail;
		aux->next = t;
		l->tail = aux->next;
		return 0;
	}
	return -1;
}

void destoy_list(List **l){
	if(*l == NULL || (*l)->head == NULL) return;
	Token* aux = (*l)->head;
	while(aux){
		Token* next=aux->next;
		free(aux);
		aux=next;
	}
	free(*l);
	*l = NULL;
}
