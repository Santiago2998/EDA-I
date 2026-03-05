#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Contacto {
    char nombre[50];
    char telefono[20];
    char correo[50];
};

//Función para limpiar el salto de línea
void limpiarSalto(char *cadena){
    cadena[strcspn(cadena, "\n")] = '\0';
}

//Función para agregar contacto
void agregarContacto(struct Contacto **agenda, int *total){
    struct Contacto *temp;

    temp = (struct Contacto *)realloc(*agenda, (*total + 1) * sizeof(struct Contacto));

    if (temp == NULL){
        printf("Error de Memoria. \n");
        return;
    }

    *agenda = temp; //Se están ligando de modo que realloc funciona para ambos

    printf("Nombre: ");
    fgets((*agenda)[*total].nombre, 50, stdin);
    limpiarSalto((*agenda)[*total].nombre);

    printf("Telefono: ");
    fgets((*agenda)[*total].telefono, 20, stdin);
    limpiarSalto((*agenda)[*total].telefono);

    printf("Correo: ");
    fgets((*agenda)[*total].correo, 20, stdin);
    limpiarSalto((*agenda)[*total].correo);

    (*total)++;
    printf("Contacto Agregado.\n");
}

//Función para mostrar contactos
void mostrarContactos(struct Contacto *agenda, int total){
    if (total == 0){
        printf("Agenda Vacia...\n");
        return;
    }

    for (int  i = 0; i < total; i++){
        printf("\nContacto %d: \n", i + 1);
        printf("Nombre: %s\n", agenda[i].nombre);
        printf("Telefono: %s\n", agenda[i].telefono);
        printf("Correo Electronico: %s\n", agenda[i].correo);
    }
    /*
        El operador de referencia (.) se usa para mostrar datos o 
        modificar información almacenada en la variable del struct

        El operador de desreferencia (->) se usa cuando se va asignar a otra variable, 
        de modo que se le dice: esta referencia lígala a esta variable.
    */
}

void mostrarMenu(){
    printf("\n----AGENDA ELECTRONICA---\n");
    printf("1. Agregar Contacto.\n");
    printf("2. Mostrar Contactos.\n");
    printf("3. Salir.\n");
    printf("Ingresa una opcion: ");
}

int main(){
    struct Contacto *agenda = NULL;
    int total = 0;
    int opcion;

    do{
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();

        switch(opcion){
            case 1:
                agregarContacto(&agenda, &total);
                break;

            case 2:
                mostrarContactos(agenda, total);
                break;
            
            case 3:
                printf("Fin de la Ejecucion...buen dia...");
                break;

            default:
            printf("Opcion no valida");
        }

    }while(opcion != 3);

    free(agenda);
    agenda = NULL;

    return 0;
}
