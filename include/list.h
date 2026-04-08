#ifndef LIST_H
#define LIST_H
#include <stddef.h>
#include "token.h"

typedef struct List List;

List* init_list();
int push_token(List** l, Token* t);
void destoy_list(List **l);

#endif
