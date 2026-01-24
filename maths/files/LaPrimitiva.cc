#include <stdio.h>

struct NumberPrimitiva {
    char year[10], first[10], second[10], third[10], quarter[10], fifth[10], sixth[10];
};

struct BestAnswer {
    char year[10];
    int niceTries;
};

char year[10], first[10], second[10], third[10], quarter[10], fifth[10], six[10];
int aciertos = 0, actualAciertos;

NumberPrimitiva AllNumbers;
BestAnswer Answer;

FILE *f;

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void DeleteSaltoLinea(char Cadena[]) {
    int len = strlen(Cadena);
    if (len > 0 && Cadena[len - 1] == '\n') {
        Cadena[len - 1] = '\0';
    }

}

void DeleteSpecialCharacters(char Cadena[]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void AskNumbers() {
    printf("Introduzca primer numero: ");
    fgets(AllNumbers.first, 10, stdin);
    DeleteSaltoLinea(AllNumbers.first);

    printf("Introduzca segundo numero: ");
    fgets(AllNumbers.second, 10, stdin);
    DeleteSaltoLinea(AllNumbers.second);

    printf("Introduzca tercer numero: ");
    fgets(AllNumbers.third, 10, stdin);
    DeleteSaltoLinea(AllNumbers.third);

    printf("Introduzca cuarto numero: ");
    fgets(AllNumbers.quarter, 10, stdin);
    DeleteSaltoLinea(AllNumbers.quarter);

    printf("Introduzca quinto numero: ");
    fgets(AllNumbers.fifth, 10, stdin);
    DeleteSaltoLinea(AllNumbers.fifth);

    printf("Introduzca sexto numero: ");
    fgets(AllNumbers.sixth, 10, stdin);
    DeleteSaltoLinea(AllNumbers.sixth);
}

void AddNumber(int Index, char NumberToAdd, int Place) {

    switch (Index) {
        case 0:
            year[Place] = NumberToAdd;
        break;
        case 1:
            first[Place] = NumberToAdd;
        break;
        case 2:
            second[Place] = NumberToAdd;
        break;
        case 3:
            third[Place] = NumberToAdd;
        break;
        case 4:
            quarter[Place] = NumberToAdd;
        break;
        case 5:
            fifth[Place] = NumberToAdd;
        break;
        case 6:
            six[Place] = NumberToAdd;
        break;
    }
}

void CheckAnswers() {
    if (AllNumbers.first[0] == first[0] &&
        AllNumbers.first[1] == first[1]) {
        actualAciertos++;
    }

    if (AllNumbers.second[0] == second[0] &&
        AllNumbers.second[1] == second[1]) {
        actualAciertos++;
    }

    if (AllNumbers.third[0] == third[0] &&
        AllNumbers.third[1] == third[1]) {
        actualAciertos++;
    }

    if (AllNumbers.quarter[0] == quarter[0] &&
        AllNumbers.quarter[1] == quarter[1]) {
        actualAciertos++;
    }

    if (AllNumbers.fifth[0] == fifth[0] &&
        AllNumbers.fifth[1] == fifth[1]) {
        actualAciertos++;
    }

    if (AllNumbers.sixth[0] == six[0] &&
        AllNumbers.sixth[1] == six[1]) {
        actualAciertos++;
    }
}

void CloseField(int Index, int Length) {
    switch (Index) {
        case 0: 
            year[Length] = '\0';
        break;
        case 1: 
            first[Length] = '\0'; 
        break;
        case 2: 
            second[Length] = '\0'; 
            break;
        case 3: 
            third[Length] = '\0'; 
        break;
        case 4: 
            quarter[Length] = '\0'; 
        break;
        case 5: 
            fifth[Length] = '\0'; 
        break;
        case 6: 
            six[Length] = '\0'; 
        break;
    }
}

int main() {

    AskNumbers();

    f = fopen("resultados.txt", "r");

    int contador = 0, startIndex = 0;
    do {

        char Character = fgetc(f);

        if (Character != ';') {
            AddNumber(startIndex, Character, contador++);
        } else {

            CloseField(startIndex, contador);
            
            startIndex++;
            contador = 0;

            if (startIndex == 8) {
                CheckAnswers();
                if (actualAciertos > aciertos) {
                    aciertos = actualAciertos;
                    for (int k = 0; k < strlen(year); k++) {
                        Answer.year[k] = year[k];
                    }
                    Answer.niceTries = actualAciertos;
                }
                actualAciertos = 0;
                startIndex = 0;
            }
        }

    } while (!feof(f));

    printf("El year con mas aciertos es: ");
    for (int i = 0; i < strlen(Answer.year); i++) {
        printf("%c", Answer.year[i]);
    }

    printf(". Y sus aciertos son: %d.", Answer.niceTries);

    return 0;
}