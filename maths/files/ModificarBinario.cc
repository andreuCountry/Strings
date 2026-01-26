#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Number;
int NumberInserted;
int Cambiado;
FILE *f;

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
    scanf("%d", &NumberInserted);

    /*for (int i = 0; i < strlen(Number); i++) {
        printf("%c", Number[i]);
    }*/
    printf("\n");

    printf("This is the number we are gonna change it: ");
    scanf("%d", &Cambiado);
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

    f = fopen("numbers.dat", "r+b");

    bool finded = false;
    while (fread(&Number, sizeof(Number), 1, f)) {

        finded = Number == NumberInserted;
        if (finded) {
            fseek(f, -1*sizeof(NumberInserted), SEEK_CUR);
            fwrite(&Cambiado, sizeof(Cambiado), 1, f);
            fseek(f, 1*sizeof(NumberInserted), SEEK_CUR);
        }
    }

    fclose(f);
    f = fopen("numbers.dat", "rb");

    while (fread(&Number, sizeof(Number), 1, f)) {
        printf("%d", Number);
        printf("  ");
    }

    fclose(f);
    
    return 0;
}