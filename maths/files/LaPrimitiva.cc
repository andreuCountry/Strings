#include <stdio.h>

char FirstPar[2], SecondPar[2], ThirdPar[2], FourthPar[2], FivePar[2], SixPar[2];

void AskNumbers() {
    printf("Introduzca un número: ");

    fgets(FirstPar, 2, stdin);
    fgets(SecondPar, 2, stdin);
    fgets(ThirdPar, 2, stdin);
    fgets(FourthPar, 2, stdin);
    fgets(FivePar, 2, stdin);
    fgets(SixPar, 2, stdin);
}

int main() {

    AskNumbers();

    for (int i = 0; i < 2; i++) {
        printf("%c", FirstPar[2]);
    }

    return 0;
}