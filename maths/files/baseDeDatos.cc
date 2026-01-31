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

ContactInfo ContactA, ContactModify;

int IDToSearch;

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void DeleteSpecialCharacters(char Cadena[]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void UpdateField(char Option) {
    // Search by actualizator.id and then replace

    Contacts = fopen("contacts.dat", "r+b");

    while (fread(&ContactA, sizeof(struct ContactInfo), 1, Contacts)) {
        bool Searched = ContactA.id == IDToSearch;

        if (Searched) {
            fseek(Contacts, -1*sizeof(ContactA), SEEK_CUR);
            switch (Option) {
                case '1':
                    for (int i = 0; i < strlen(Chain); i++) {
                        ContactA.name[i] = Chain[i];
                    }
                break;
                case '2':
                    for (int j = 0; j < strlen(Chain); j++) {
                        ContactA.surname_1[j] = Chain[j];
                    }
                break;
                case '3':
                    for (int r = 0; r < strlen(Chain); r++) {
                        ContactA.surname_2[r] = Chain[r];
                    }
                break;
                case '4':
                    for (int k = 0; k < strlen(Chain); k++) {
                        ContactA.phone[k] = Chain[k];
                    }
                break;
                case '5':
                    for (int l = 0; l < strlen(Chain); l++) {
                        ContactA.email[l] = Chain[l];
                    }
                break;
            }
            fwrite(&ContactA, sizeof(ContactA), 1, Contacts);
            fseek(Contacts, 1*sizeof(ContactA), SEEK_CUR);
        }
    }

    fclose(Contacts);
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
    DeleteSpecialCharacters(Chain);

    if (Option == '4' && strlen(Chain) > 12) {
        printf("El campo debe ocupar menos de 12 caracteres ... \n");
        MenuUpdateField('4');
    }

    printf("\n");

    if (Option != '6') {
        printf("De que usuario (ID) vas a querer cambiar ese campo? ");
        scanf("%d", &IDToSearch);

    }
    
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

bool Validate() {
    if ((Contacts = fopen("contacts.dat", "rb")) == NULL) {
        printf("Error. El fichero contacts.dat no existe");
        printf("\n\n");

        return false;
    } else {
        return true;
    }
}

void Consultar() {

    bool IsValid = Validate();

    if (IsValid) {
        Contacts = fopen("contacts.dat", "rb");

        printf("ID --   NOMBRE   --   APELIIDO   --   SEG_APELLIDO   --   TELEFONO   --   EMAIL         | \n");
        printf("_________________________________________________________________________________________ \n");

        while (fread(&ContactModify, sizeof(struct ContactInfo), 1, Contacts)) {
            if(ContactModify.id != 0) {
                
                printf("%d   --   ", ContactModify.id);
                printf("%s   --   ", ContactModify.name);
                printf("%s   --   ", ContactModify.surname_1);
                printf("%s   --   ", ContactModify.surname_2);
                printf("%s   --   ", ContactModify.phone);
                printf("%s", ContactModify.email);
                printf("\n");
            }
        }

        fclose(Contacts);

        printf("\n\n");
    }
}

void Updatear() {

    printf("Que campo quieres modificar?");
    ShowUpdateMenu();
}

void Insert() {

    Contacts = fopen("contacts.dat", "a+b");

    ContactInfo ContactInserted;
    
    printf("Introduzca nombre: ");
    fgets(ContactInserted.name, 80, stdin);
    DeleteSpecialCharacters(ContactInserted.name);
    printf("\n");

    printf("Introduzca primer apellido: ");
    fgets(ContactInserted.surname_1, 80, stdin);
    DeleteSpecialCharacters(ContactInserted.surname_1);
    printf("\n");

    printf("Introduzca segundo apellido: ");
    fgets(ContactInserted.surname_2, 80, stdin);
    DeleteSpecialCharacters(ContactInserted.surname_2);
    printf("\n");

    printf("Introduzca telefono: ");
    fgets(ContactInserted.phone, 12, stdin);
    DeleteSpecialCharacters(ContactInserted.phone);
    printf("\n");

    printf("Introduzca email: ");
    fgets(ContactInserted.email, 40, stdin);
    DeleteSpecialCharacters(ContactInserted.email);
    printf("\n");


    // Last id associated, search and add one plus
    int contador = 0;
    while(fread(&ContactA, sizeof(struct ContactInfo), 1, Contacts)) {
        contador++;
    }

    ContactInserted.id = contador + 1;

    fwrite(&ContactInserted, sizeof(ContactInserted), 1, Contacts);

    fclose(Contacts);
}

void Delete() {
    Contacts = fopen("contacts.dat", "r+b");

    printf("De que usuario (ID) vas a querer cambiar ese campo? ");
    scanf("%d", &IDToSearch);

    while (fread(&ContactA, sizeof(struct ContactInfo), 1, Contacts)) {
        bool Searched = ContactA.id == IDToSearch;

        if (Searched) {
            ContactA.id = 0;
            fseek(Contacts, -1*sizeof(ContactA), SEEK_CUR);
            fwrite(&ContactA, sizeof(ContactA), 1, Contacts);
            fseek(Contacts, 1*sizeof(ContactA), SEEK_CUR);
        }
    }
    fclose(Contacts);
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

int main() {

    ShowMenu();

    return 0;
}