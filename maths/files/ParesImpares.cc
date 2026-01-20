#include <stdio.h>
#include <stdlib.h>

FILE *f, *pares, *impares;
int valor;

int format(int valor) {

    return valor;
}

int main() {

    f = fopen("numeros.dat", "rb");

    pares = fopen("pares.dat", "wb");
    impares = fopen("impares.dat", "wb");

    while (fread(&valor, sizeof(valor), 1, f)) {
        if (valor % 2 == 0) {
            fwrite(&valor, sizeof(valor), 1, pares);
        } else {
            fwrite(&valor, sizeof(valor), 1, impares);
        }
    }

    fclose(f);
    fclose(pares);
    fclose(impares);

    // Despues, de la lecturita, se viene el formateo

    printf("Escoge que quieres ver: impares(i) o  pares(p) \n");
    char Letter;
    scanf(&Letter);

    printf("________________________________________________________________ \n");

    if (Letter == 'i') {
        impares = fopen("impares.dat", "rb");

        while (fread(&valor, sizeof(valor), 1, f)) {
            format(valor);

        }
    } else {
        pares = fopen("pares.dat", "rb");

        while (fread(&valor, sizeof(valor), 1, f)) {
            format(valor);
        }
    }

    return 0;
}