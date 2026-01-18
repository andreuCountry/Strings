#include <stdio.h>
#include <string.h>

char Cadenita[1000] = {'\0'}, NewCadenita[1000] = {'\0'};

void DeleteSpecialCharacters(char Cadena[80]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void ReverseWord(char Cadena[80]) {
    
    int Length = strlen(Cadena);
    char Aux;

    for (int i = 0; i < Length / 2; i++) {
        // Necesito una auxiliar para guardar el caracter
        Aux = Cadena[i];
        // Necesito cambiar el ultimo caracter para asignarlo al ultimo
        Cadena[i] = Cadena[Length - i - 1];
        Cadena[Length - i - 1] = Aux;
    }
}

int main() {

    printf("Frase para hacer reverse: ");
    fgets(Cadenita, 1000, stdin);

    DeleteSpecialCharacters(Cadenita);

    char *CadenitaTroz = strtok(Cadenita, " ");

    while (CadenitaTroz) {
        ReverseWord(CadenitaTroz);
        printf("%s ", CadenitaTroz);
        CadenitaTroz = strtok(NULL, " ");
    }

    printf("\n");

    return 0;
}