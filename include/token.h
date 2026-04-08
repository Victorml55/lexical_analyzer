#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_type{
	VARIABLES = 1,
	KEY_WORD = 2,
	NUMBER = 3,
	OPERATION = 4,
	UNKNOWN = -1
}Token_type;

typedef struct Token{
	struct Token* next;
	char* lexeme;
	Token_type type;
}Token;

#endif
