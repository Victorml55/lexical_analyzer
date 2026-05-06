#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/list.h"
#include "include/dfa.h"
#include "include/token.h"
#include "include/parser.h"

int main(){
	char *input = "x = (3+2)";
	List* tokens = tokenize(input);     
	print_list(tokens);
	Parser* p = parser_init(tokens);
	ASTNode* ast = parse_program(p);
	ast_print(ast, 0);                  
	ast_free(ast);
	parser_free(p);
	return 0;

}

