#include <stdio.h>

FILE *f;

int main() {

    f = fopen("texto0.txt", "w");
    fclose(f);
    
    return 0;
}