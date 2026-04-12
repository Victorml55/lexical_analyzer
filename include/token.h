#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_type{
	VARIABLE = 1, //alfa (hecho)
	KEYWORD = 2, //alfa (hecho)
	NUMBER = 3,
	OPERATION = 4, //(hecho)
	STRING = 5,
	UNKNOWN = -1 //(hecho)
}Token_type;

typedef struct Token{
	struct Token* next;
	char* lexeme;
	Token_type type;
}Token;

Token* init_token();
void print_token(Token* t);

#endif
