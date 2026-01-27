#include <stdio.h>
#include <conio.h>

FILE *Contacts;
char Chain[80];

struct ContactInfo {
    int id;
    char name[80], surname_1[80], surname_2[80];
    char phone[12];
    char email[40];
};

struct Actualizator {
    char id[20];
    char field[20];
    char UpdatedField[50];
};

ContactInfo Contact;

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void UpdateField(char Option) {
    // Utilizar Actualizator
}

void MenuUpdateField(char Option) {
    switch (Option) {
        case '1':
            printf("Introduzca nombre a cambiar: ");
        break;
        case '2':
            printf("Introduzca apellido a cambiar: ");
        break;
        case '3':
            printf("Introduzca segundo apellido a cambiar: ");
        break;
        case '4':
            printf("Introduzca telefono a cambiar: ");
        break;
        case '5':
            printf("Introduzca email a cambiar: ");
        break;
    }

    fgets(Chain, 80, stdin);

    UpdateField(Option);
}

void ShowUpdateMenu() {
    char Option;

    printf("\n");
    printf("1 -- Modificar el nombre \n");
    printf("2 -- Modificar el primer apellido \n");
    printf("3 -- Modificar el segundo apellido \n");
    printf("4 -- Modificar el telefono \n");
    printf("5 -- Modificar el email \n");
    printf("6 -- Ninguno \n");

    Option = getch();

    printf("\n");

    if (Option < 49 && Option > 53) {
        printf("El numero introducido no corresponde a ninguna secuencia. \n");
    } else {
        MenuUpdateField(Option);
    }

    if (Option != '6') {
        ShowUpdateMenu();
    }
}

void Consultar() {
    Contacts = fopen("contacts.dat", "rb");

    while (fread(&Contact, sizeof(struct ContactInfo), 1, Contacts)) {
        for (int i = 0; i < strlen(Contact.name); i++) {
            printf("%c", Contact.name[i]);
        }
    }

    fclose(Contacts);

    printf("\n\n");
}

void Updatear() {

    printf("Que campo quieres modificar?");
    ShowUpdateMenu();
}

void Insert() {
    Contacts = fopen("contacts.dat", "ab");
    
    printf("Introduzca nombre: ");
    fgets(Contact.name, 80, stdin);
    printf("\n");

    printf("Introduzca primer apellido: ");
    fgets(Contact.surname_1, 80, stdin);
    printf("\n");

    printf("Introduzca segundo apellido: ");
    fgets(Contact.surname_2, 80, stdin);
    printf("\n");

    printf("Introduzca telefono: ");
    fgets(Contact.phone, 12, stdin);
    printf("\n");

    printf("Introduzca email: ");
    fgets(Contact.email, 40, stdin);
    printf("\n");

    fwrite(&Contact, sizeof(Contact), 1, Contacts);

    fclose(Contacts);
}

void Delete() {

}

void ShowMenu() {
    char Option;

    printf("Que desea hacer? \n");
    printf("1 -- Consultar la base. \n");
    printf("2 -- Updatear la base. \n");
    printf("3 -- Insertar dentro de la base. \n");
    printf("4 -- Delete de un contacto de la base. \n");
    printf("5 -- Salir. \n");
    Option = getch();

    switch (Option) {
        case '1':
            Consultar();
        break;
        case '2':
            Updatear();
        break;
        case '3':
            Insert();
        break;
        case '4':
            Delete();
        break;
    }

    if (Option != '5') {
        ShowMenu();
    }
}

void CreateBBDD() {
    Contacts = fopen("contacts.dat", "wb");

    char Cadena[100] = "ID   --   NOMBRE   --   APELLIDO   --   SEGUNDO_APE   --   TELEFONO   --   EMAIL        |";
    fwrite(&Cadena, sizeof(Cadena), 1, Contacts);
    char Cadena2[100] = "_________________________________________________________________________________________";
    fwrite(&Cadena2, sizeof(Cadena2), 1, Contacts);
    fclose(Contacts);

}

int main() {

    CreateBBDD();

    ShowMenu();

    return 0;
}