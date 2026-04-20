#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"

char* get_file_content(const char* route) {
    FILE* file = fopen(route, "rb"); //read binary para asignar el tamaño del archivo al buffer
    if (!file) return NULL;

    //calcular el tamaño del archivo moviendo el puntero al final
    fseek(file, 0, SEEK_END);
    long size = ftell(file); //calcula la posicion del puntero y la asigna a size
    rewind(file);

    char* buffer = (char*)malloc(size + 1); //reserva de memoria
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    
    fclose(file);
    return buffer;
}

int main(){
	List* l = init_list();

	print_list(l);

	//prueba de lectura hermanito jeje
	printf("%s\n", get_file_content("test2.ked"));

	return 0;
}