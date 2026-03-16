#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
int id;
float precio;
char nombre [50];
} Productos;

void registrarProductos(Productos *llenado, int n){
    for (int i = 0; i < n; i++){
        printf("\nProducto %d\n", i + 1);
        printf("Id: ");
        scanf("%d", &llenado[i].id);
        getchar();
        printf("Precio: ");
        scanf("%f", &llenado[i].precio);
        getchar();
        printf("Nombre: ");
        fgets(llenado[i].nombre, 50, stdin);
        llenado[i].nombre[strcspn(llenado[i].nombre, "\n")] = '\0';
    }
    printf("Productos registrados.\n");
}

//Nombre del 1er struct = Producto
void showProductTicket(Productos *show, int carrito){
    float totalProductos = 0;
    if (carrito == 0) {
        printf ("No ha añadido ningún producto a su carrito.\n regresando...\n");
        return;
    }
    for (int i = 0; i < carrito; i++){
        printf("Id: %d, \nProducto: %s \t  Precio: %.2f\n",show[i].id,show[i].nombre, show[i].precio);
        totalProductos += show[i].precio;
    }
    printf("Total a pagar: %.2f\n", totalProductos);
    return; 
}

void mostrarCarrito(Productos *puntero, int n){
    for (int i = 0; i < n; i++){
        printf("\n-------Ticket----------\n");
        printf("| ID: %d\t| Nombre: %s\t| Precio: %.2f |\n", puntero[i].id, puntero[i].nombre, puntero[i].precio);
    }
}

int main(){
    //Menu
    int opcion;
    Productos *llenado = NULL;
    int tam;
    //datos y mostrar salir
    do {
        printf("--- Carrito---\n");
        printf("1.Ingresar productos: \n ");
        printf("2.Mostrar carrito: \n");
        printf("3. Salir\n");
        printf("Seleccione una opción \n");
        scanf("%d", &opcion); 
        getchar();
        switch (opcion){
            case 1:
            //Tamaño del carrito
            printf("Ingresa el tamaño del carrito: ");
            scanf("%d", &tam);
            getchar();
    
            llenado = (Productos *)malloc(tam * sizeof(Productos));

            if (llenado == NULL){
                printf("Error de memoria\n");
            } else{
                registrarProductos(llenado, tam);
            }
            break; 
            case 2:
            mostrarCarrito(llenado, tam);
            break;
            case 3: 
            showProductTicket(llenado, tam);
            break;
            default:
            printf("Opción no valida\n");
        }

    } while(opcion != 3);
    
    free(llenado);
    llenado = NULL;
    return 0;
}
