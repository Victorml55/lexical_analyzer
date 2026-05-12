#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/list.h"
#include "include/dfa.h"
#include "include/token.h"
#include "include/parser.h"

char* get_content(FILE* file);

int main(int argc, char **argv){
	if(argv[1]){
		char *path = argv[1];
		FILE* file = fopen(path, "r");
		if(!file) return -1;
		char *input = get_content(file);
		List* tokens = tokenize(input);     
		Parser* p = parser_init(tokens);
		ASTNode* ast = parse_program(p);
		ast_print(ast, 0);                  
		ast_free(ast);
		parser_free(p);

	}else{
		char *input = "x = (20 + 20) / (20 + 20 / 7)";
		List* tokens = tokenize(input);     
		//print_list(tokens);
		Parser* p = parser_init(tokens);
		ASTNode* ast = parse_program(p);
		ast_print(ast, 0);                  
		ast_free(ast);
		parser_free(p);
		
	}

	return 0;
}

char* get_content(FILE* file){

	if (file == NULL) {
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char* buffer = malloc(size + 1);
	if (buffer == NULL) {
		return NULL;
	}

	size_t read_size = fread(buffer, 1, size, file);

	buffer[read_size] = '\0';

	return buffer;
}
