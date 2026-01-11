#include <stdio.h>
#include <string.h>

char CorrectAnswer[6] = {"salir"}, Answer[80] = {'\0'}, AuxAnswer[80] = {'\0'}, NextLine[1] = {'\n'};

void DeleteSpecialCharacters(char Cadena[80]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void ReverseWord(char Cadena[80]) {
    
    // Guardar cadena para compararla, copiando porque los arrays son direcciones de memoria
    strcpy(AuxAnswer, Cadena);

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

    int Tries = 0;

    char TotalCharacters[1600] = {'\0'};

    do {
        fgets(Answer, 80, stdin);
        DeleteSpecialCharacters(Answer);

        ReverseWord(Answer);

        if (strcmp(CorrectAnswer, strlwr(AuxAnswer)) != 0) {
            strcat(TotalCharacters, Answer);
            strcat(TotalCharacters, NextLine);
        }

        Tries++;

    } while (strcmp(CorrectAnswer, strlwr(AuxAnswer)) != 0 && Tries != 20);

    printf("Volcado cadenas introducidas orden inverso. \n");
    fputs(TotalCharacters, stdout);

    return 0;
}