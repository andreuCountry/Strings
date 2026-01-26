#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Number;
int NumberToDeleted;
FILE *f, *kobeBryant;

void Semilla() {
    srand(time(NULL));
}

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void AskNumber() {

    printf("Ask for a number: ");
    scanf("%d", &NumberToDeleted);

    /*for (int i = 0; i < strlen(Number); i++) {
        printf("%c", Number[i]);
    }*/
}

int main() {

    Semilla();

    f = fopen("numbers.dat", "wb");

    for (int i = 0; i < 10; i++) {

        int numberInsert = rand()%101;

        fwrite(&numberInsert, sizeof(numberInsert), 1, f);
    }

    fclose(f);

    f = fopen("numbers.dat", "rb");

    while (fread(&Number, sizeof(Number), 1, f)) {
        printf("%d", Number);
        printf("  ");
    }

    fclose(f);

    printf("\n");

    AskNumber();

    f = fopen("numbers.dat", "rb");
    kobeBryant = fopen("numbersAux.dat", "wb");

    bool finded = false;
    while (fread(&Number, sizeof(Number), 1, f)) {

        finded = Number == NumberToDeleted;
        if (!finded) {
            fwrite(&Number, sizeof(Number), 1, kobeBryant);
        }
    }

    fclose(f);
    fclose(kobeBryant);

    kobeBryant = fopen("numbersAux.dat", "rb");

    while (fread(&Number, sizeof(Number), 1, kobeBryant)) {
        printf("%d", Number);
        printf("  ");
    }

    fclose(kobeBryant);
    
    return 0;
}