#include <stdio.h>

FILE *f;
int i, valor;

int main() {

    f = fopen("numeros.dat", "wb");

    for (int i = 0; i < 5; i++) {

        printf("Numero: ");
        scanf("%d", &valor);
        fwrite(&valor, sizeof(valor), 1, f);
    }

    fclose(f);

    f = fopen("numeros.dat", "rb");

    while (fread(&valor, sizeof(valor), 1, f)) {
        printf("%d \n", valor);
    }

    fclose(f);

    return 0;
}