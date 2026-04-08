#include <stdio.h>
#include <stdlib.h>

int classify_words(char* word);

int main(){
	printf("hola mundo\n");
	FILE *file = fopen("test.txt", "r");
	if(!file){
		printf("no se pudo abrir el archivo");
		return -1;
	}
	char c;
	int counter = 0;
	while((c = fgetc(file)) != EOF){
		if(c == ' ') counter++;
		printf("%c", c);
	}
	printf("\nnumero de palabras %i", counter);
	return 0;
}

int classify_words(char* word){
	return 0;
}
