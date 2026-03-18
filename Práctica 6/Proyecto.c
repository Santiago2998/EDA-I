//Hay dostipos de servicio cola circular para los usuarios normales
//Cola doble: Usuarios VIP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definir structs para usuarios VIP
struct vipNodo{
    int turno;
    char name[50];
    struct vipNodo *ant;
    struct vipNodo *sig;
};

struct vipCola{
    struct vipNodo *frente;
    struct vipNodo *final; 
};
//definir estructuras de usuarios normales
struct normalNodo{
    int turno;
    char name[50];
    struct normalNodo *sig;
};

struct normalCola{
    struct normalNodo *final;
};

//funciones de apoyo
void cleanLineJump(char *cadena){
    int i =0;
    while (cadena[i]!= '\0'){
        if (cadena[i] == '\n'){
            cadena[i] = '\0';
        }
        i++;
    }
}
//operaciones de colaVIP - cola doble
//Solo se puede encolar en un sentido


int vipAtend(struct vipCola *cola, int *turno, char name[50]){
    struct vipNodo *temporal;
    if (vipColaEmpty(cola)){
        return 0;
    }

    temporal= cola-> frente;
    *turno = temporal -> turno;
    strcpy(name, temporal-> name);

if (cola -> frente == cola -> final){
    cola -> frente = NULL;
    cola -> final = NULL;
    }else{
        cola -> frente = temporal -> sig;
        cola -> frente -> ant = NULL;
    }
    free(temporal);
    return 1;
}

//Mostra cola VIP

//Operaciones de usuarios normales, atender = DESENCOLAR

//Atención mixta

void atenderSig(struct vipCola *vip, struct normalCola *normal){
    int turno;
    char name[50];
    if (vipAtend(vip, &turno, name)){
        printf("\nSe atiende usuario VIP: \n");
        printf("Turno VIP %d - %s\n",turno,name);
        }else if (normalAtend(normal,&turno,name)){
            printf("\nSe atiende usuario normal: \n");
        printf("Turno normal %d - %s\n",turno,name);
        } else {
            printf("no hay usuarios en espera.\n");
        }
}
void printMenu(int option, char name[50]){
    printf("1.- Reg VIP user\n");
    printf("2.- Reg average user\n");
    printf("3.- Atender sig user\n");
    printf("4.- show colas\n");
    printf("5 Salir.- Reg VIP user\n");

    switch (option)
    {
    case 1:
        printf("ingrese el nombre del usuario VIP: ");
        fgets(name, sizeof(name),stdin);
        cleanLineJump(name);
        
        insertarVIP(&vipCola,vipCount, name);
        printf("User VIP registrado con turno VIP %d.\n", vipCount);
        vipCount++;
    break;
    case 2:
        printf("ingrese el nombre del usuario: ");
        fgets(name, sizeof(name),stdin);
        cleanLineJump(name);
        
        insertarVIP(&normalCola,normalCount, name);
        printf("User registrado con turno %d.\n", vipCount);
        vipCount++;
    break;
    case 3:
        atenderSig(&vipCola, &normalCola);
    break;
    case 4:
        vipShow();
        normalShow();
    break;
    case 5:
        printf("saliendo...");
    default:
        break;
    }
}


//Utilizar la liberación de colas doble y circular


//Espacio para implementar la libreración de memoria.
int main(){
    struct vipCola vipCola;
    struct normalCola normalCola;

    int option;
    int vipCount = 1, normalCount = 1;
    char name[50];

    beginVipCola(&vipCola);
    beginNormalCola(&normalCola);
    do{
        printf("=== SISTEMA MIXTO DE ATENCION ===\n");

        printMenu(option,name);
    } while (option != 5);
}
