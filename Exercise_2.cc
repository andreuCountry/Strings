#include <stdio.h>
#include <string.h>

char CorrectAnswer[6] = {"salir"}, Answer[80] = {'\0'}, NextLine[1] = {'\n'};

void DeleteSpecialCharacters(char Cadena[80]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

int main() {

    int Tries = 0;

    char TotalWords[1600] = {'\0'};

    do {
        fgets(Answer, 80, stdin);
        DeleteSpecialCharacters(Answer);

        
        if (strcmp(CorrectAnswer, strlwr(Answer)) != 0) {
            strcat(TotalWords, Answer);
            strcat(TotalWords, NextLine);
        }

        Tries++;

    } while (strcmp(CorrectAnswer, strlwr(Answer)) != 0 && Tries != 20);

    printf("Volcado cadenas introducidas orden inverso. \n");
    fputs(TotalWords, stdout);

    return 0;
}