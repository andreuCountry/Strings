#include <stdio.h>
#include <string.h>

char Cadena1[50] = {"\0"};

void DeleteSpecialCharacters(char Cadena[50]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

int main() {

    fgets(Cadena1, 50, stdin);
    printf("Caracteres: %d\n", strlen(Cadena1));
    DeleteSpecialCharacters(Cadena1);
    printf("Caracteres: %d\n", strlen(Cadena1));    

    fgets(Cadena1, 50, stdin);
    printf("%d\n", strlen(Cadena1));
    fputs(Cadena1, stdout);

    return 0;
}