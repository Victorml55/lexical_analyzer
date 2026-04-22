#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/list.h"
#include "include/dfa.h"
#include "include/token.h"

char* get_file_content(const char* route) {
    FILE* file = fopen(route, "rb");
    if (!file) {
	    printf("FILE not found\n");
	    return NULL;	    
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file); 
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    
    fclose(file);
    return buffer;
}


int main(int argc, char* argv[]){
	if(argv[1]){
		char* path = argv[1];
		char* input = get_file_content(path);
		if(!input) return -1;
		List* l = tokenize(input);
		print_list(l);
		return 0;
	}else{
		printf("modo sin archivo\n");
		char* input;
		
	}
	return 0;
}
