#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Productos {
    int codigo;
    float precio;
    char tipo[50];
};

void limpiarSalto(char *cadena){
    cadena[strcspn(cadena, "\n")] = '\0';
}

void registrarProducto(struct Productos **producto, int *total){
    struct Productos *temp;
    char continuar;

    temp = (struct Productos *)realloc(*producto, (*total + 1) * sizeof(struct Productos));

    if (temp == NULL){
        printf("Error de Memoria.\n");
        return;
    }

    *producto = temp;

    printf("Codigo del producto: ");
    scanf("%d", &(*producto)[*total].codigo);
    getchar();

    printf("Precio del producto: ");
    scanf("%f", &(*producto)[*total].precio);
    getchar();

    printf("Tipo de producto: ");
    fgets((*producto)[*total].tipo, 50, stdin);
    limpiarSalto((*producto)[*total].tipo);

    printf("Desea simular un descuento? (s/n): ");
    scanf("%c", &continuar);
    getchar();

    if (continuar == 's' || continuar == 'S'){
        double descuento = 0;
        for (int i = 0; i < 3; i++){
            descuento += ((*producto)[*total].precio * 0.2);
        }
        (*producto)[*total].precio -= descuento;

        printf("Precio con descuento: %.2f\n", (*producto)[*total].precio);
    }else {
        printf("El producto se queda con el precio regular.\n");
    }

    printf("Desea simular incremento de precio? (s/n): ");
    scanf("%c", &continuar);
    getchar();

    while (continuar == 's' || continuar == 'S'){
        (*producto)[*total].precio += 5;
        printf("Nuevo Precio: %.2f\n", (*producto)[*total].precio);
        printf("Continuar incrementando? (s/n)\n");
        scanf("%c", &continuar);
        getchar();
    }

    (*total)++;
    printf("Producto Registrado.\n");

}

void mostrarInventario(struct Productos *producto, int total){
    if (total == 0){
        printf("Sin Productos Registrados.\n");
        return;
    }

    for (int i = 0; i < total; i++){
        printf("----------------------Producto %d--------------------\n", i + 1);
        printf("| Codigo: %d\tPrecio: %.2f\tTipo: %s |\n", producto[i].codigo, producto[i].precio, producto[i].tipo);
    }
    printf("----------------------------------------------------\n");
}

void buscarProducto(struct Productos *producto, int total, int codigoBuscado){
    for (int i = 0; i < total; i++){
        if (producto[i].codigo == codigoBuscado){
            printf("Producto con codigo %d encontrado\n", producto[i].codigo);
            printf("Precio: %.2f\n", producto[i].precio);
            printf("Tipo: %s\n", producto[i].tipo);
            return;
        }
    }
    printf("Producto con codigo %d No encontrado", codigoBuscado);
}

void menu(){
    printf("======Sistema de Punto de Venta=======\n");
    printf("1. Registrar Producto\n");
    printf("2. Mostrar Inventario\n");
    printf("3. Buscar Producto\n");
    printf("4. Salir\n");
    printf("Ingresa una opcion: ");
}

int main(){
    struct Productos *producto = NULL;
    int total = 0;
    int opcion, codigoBuscado;

    do{
        menu();
        scanf("%d", &opcion);
        getchar();

        switch (opcion){
            case 1:
                registrarProducto(&producto, &total);
                break;
            
            case 2:
                mostrarInventario(producto, total);
                break;
            
            case 3:
                printf("Ingresa el codigo de producto a buscar: ");
                scanf("%d", &codigoBuscado);
                buscarProducto(producto, total, codigoBuscado);
                break;

            case 4:
                printf("Cerrando....");
                break;
            
            default:
                printf("Opcion no valida");
        }

    }while (opcion != 4);

    free(producto);
    producto = NULL;

    return 0;
}