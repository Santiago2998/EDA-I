#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Productos{
    int id;
    float precio;
    char nombre[50];
    struct Productos *anterior;
    struct Productos *siguiente;
};

//

struct Productos* crearNodo(int llave, float precio, char nom[]){
    struct Productos *nuevo= (struct Productos *)malloc(sizeof(struct Productos));
    if(nuevo == NULL){
        printf("Error no se puede asignar memoria\n");
        return NULL;
    }

    nuevo->id= llave;
    nuevo->precio = precio;
    strcpy(nuevo->nombre, nom);
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

//

void insertarFinal(struct Productos **cabeza, int llave, int precio, char nom[]){
    struct Productos *nuevo = crearNodo(llave, precio, nom);
    struct Productos *actual;

    if(nuevo==NULL){
        return;
    }

    if(*cabeza==NULL){
        *cabeza = nuevo;
        return; 
    }

    actual = *cabeza;
    while(actual->siguiente!=NULL){
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo;
    nuevo->anterior = actual;

    printf("Producto Agregado.\n");
}

//funcion buscar 

struct Productos *buscar(struct Productos *cabeza, int idBuscado){
    struct Productos *actual=cabeza;
    while(actual!=NULL){
        if(actual->id==idBuscado){
            return actual;
        }
     actual = actual->siguiente;
    }
   return NULL;

}


void deleteNode(struct Productos **head, int idDelete){
    struct Productos *eliminado = buscar(*head, idDelete);

    if (eliminado == NULL){
        printf("No se pudo eliminar el Productos ya que es inexistente");
        return;
    }
    //Caso del Productos en head
    if (eliminado->anterior == NULL){
        *head = eliminado->siguiente;
        if(*head != NULL){
            (*head)->anterior = NULL;
        }
        else {
            eliminado->anterior->siguiente = eliminado -> siguiente; 
        }
    }
    //Si el Productos final tiene un dato
    if (eliminado -> siguiente != NULL){
        eliminado -> siguiente ->anterior = eliminado -> anterior;   
    }

    free(eliminado);
    printf("Producto eliminado.\n");
}

void showListFrente(struct Productos *head){
    struct Productos *actual = head;
    if(head == NULL){
        printf("El carrito esta vacio.\n");
        return;
    }

    int i = 1;
    printf("Mostrando carrito por el frente:\n");
    while(actual != NULL){
        printf("-------Producto #%d------\n", i);
        printf("ID: %d\n", actual->id);
        printf("Nombre Producto: %s\n", actual->nombre);
        printf("Precio Producto: %f\n", actual->precio);
        actual = actual->siguiente;
        i++;
    }
    printf("\n");
}

void showListFinal(struct Productos *head){
    struct Productos *actual = head;
    if(head == NULL){
        printf("El carrito esta vacio.\n");
        return;
    }

    while(actual->siguiente != NULL){
        actual = actual->siguiente;
    }

    int i = 1;
    printf("Mostrando carrito por el final:\n");
    while(actual != NULL){
        printf("-------Producto #%d------\n", i);
        printf("ID: %d\n", actual->id);
        printf("Nombre Producto: %s\n", actual->nombre);
        printf("Precio Producto: %f\n", actual->precio);
        actual = actual->anterior;
        i++;
    }
    printf("\n");
}

float sumar(struct Productos *head){
    struct Productos *actual = head;
    if(head == NULL){
        printf("El carrito esta vacio.\n");
        return 0;
    }
    float suma = 0;
    while(actual != NULL){
        suma += actual->precio;
        actual = actual->siguiente;
    }
    return suma;
}

int main(){
    //Menu
    int opcion;
    struct Productos *llenado = NULL;
    struct Productos *encotrado;
    int id = 1;
    int idDelete;
    char nombre[50];
    float precio;
    //datos y mostrar salir
    do {
        printf("--- Carrito---\n");
        printf("1.Ingresar productos: \n");
        printf("2.Eliminar Producto: \n");
        printf("3. Mostrar Carrito Por Inicio\n");
        printf("4. Mostrar Carrito Por Final\n");
        printf("5.Salir.\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion); 
        getchar();
        switch (opcion){
            case 1:
            printf("Ingresa Nombre del producto: ");
            fgets(nombre, 50, stdin);
            nombre[strcspn(nombre, "\n")] = '\0';
            printf("Ingresa Precio del Productos: ");
            scanf("%f", &precio);
            getchar();
            insertarFinal(&llenado, id, precio, nombre);
            id++;
            break; 

            case 2:
            showListFrente(llenado);
            printf("ID a eliminar: ");
            scanf("%d", &idDelete);
            getchar();
            deleteNode(&llenado, idDelete);
            break;
            case 3: 
            showListFrente(llenado);
            break;

            case 4:
            showListFinal(llenado);
            break;

            case 5:
            printf("Su ticket es:\n");
            showListFrente(llenado);
            float suma = sumar(llenado);
            printf("TOTAL : %.2f", suma);
            printf("Saliendo...\n");
            break;
            default:
            printf("Opción no valida\n");
        }

    } while(opcion != 5);
    
    
    return 0;
}
