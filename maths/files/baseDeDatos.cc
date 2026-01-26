#include <stdio.h>

char Option;
FILE *f, *p;

struct ContactInfo {
    int id;
    char name[80], surname_1[80], surname_2[80];
    char phone[12];
    char email[40];
};

struct Actualizator {
    char field[20];
    char UpdatedField[50];
};

void ShowUpdateMenu() {

}

void Consultar() {

}

void Updatear() {
    ShowUpdateMenu();


}

void Insert() {

}

void Delete() {

}

void ValidateOption(int Option) {
    
    switch (Option) {
        case 1:
            Consultar();
        break;
        case 2:
            Updatear();
        break;
        case 3:
            Insert();
        break;
        case 4:
            Delete();
        break;
    }

    if (Option != 5) {
        ShowMenu();
    }
}

void ShowMenu() {

    printf("Que desea hacer? \n");
    printf("1 -- Consultar la base. \n");
    printf("2 -- Updatear la base. \n");
    printf("3 -- Insertar dentro de la base. \n");
    printf("4 -- Delete de un contacto de la base. \n");
    printf("5 -- Salir.");
}

int main() {

    ShowMenu();

    return 0;
}