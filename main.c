#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/dfa.h"

char* get_file_content(const char* route) {
    FILE* file = fopen(route, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file); 
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    
    fclose(file);
    return buffer;
}

int main(){

	printf("%s\n", get_file_content("test2.ked"));

	return 0;
}
