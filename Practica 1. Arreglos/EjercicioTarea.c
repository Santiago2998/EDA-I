#include <stdio.h>

void registrarProducto();
double calcularDescuento(double precio);
void clasificarProducto(char tipo);
int factorial(int n);
void mostrarProductos();
void buscarProducto(int codigo);

int totalProductos = 0;
double precio[100];
int codigo[100];
char tipo[100];

int main() {
    int opcion;

    do {
        printf("\n===== Sistema de Punto de Venta =====\n");
        printf("1. Registrar producto.\n");
        printf("2. Calcular factorial promocional.\n");
        printf("3. Mostrar inventario.\n");
        printf("4. Buscar producto.\n");
        printf("5. Salir.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarProducto();
                break;

            case 2: {
                int numero;
                printf("Ingresa el numero para el factorial: ");
                scanf("%d", &numero);

                if (numero < 0) {
                    printf("No existe factorial para numeros negativos.\n");
                } else {
                    printf("Factorial de %d = %d\n", numero, factorial(numero));
                }
                break;
            }

            case 3:
                mostrarProductos();
                break;

            case 4: {
                int codigoBuscado;
                printf("Ingresa el codigo del producto a buscar: ");
                scanf("%d", &codigoBuscado);
                buscarProducto(codigoBuscado);
                break;
            }

            case 5:
                printf("Gracias por su confianza. Buen dia c:\n");
                break;

            default:
                printf("Opción no valida...\n");
        }
    } while (opcion != 5);

    return 0;
}

void registrarProducto() {

    char continuar;

    if (totalProductos >= 100) {
        printf("No se pueden registrar mas productos.\n");
        return;
    }

    printf("\nIngresa el codigo del producto: ");
    scanf("%d", &codigo[totalProductos]);

    printf("Ingresa el precio: ");
    scanf("%lf", &precio[totalProductos]);

    printf("Ingresa el tipo de producto, O=Organico, P=Procesado, L=Liquido: ");
    scanf(" %c", &tipo[totalProductos]);

    printf("Deseas simular un descuento? (s/n): ");
    scanf(" %c", &continuar);

    if (continuar == 's') {
        double descuento = calcularDescuento(precio[totalProductos]);
        printf("Precio con descuento: %.2f\n", descuento);
        precio[totalProductos] = descuento;
    } else {
        printf("Producto se queda con precio regular.\n");
    }

    clasificarProducto(tipo[totalProductos]);


    printf("Deseas simular incremento de precio? (s/n): ");
    scanf(" %c", &continuar);

    while (continuar == 's') {
        precio[totalProductos] += 5;
        printf("Nuevo precio: %.2f\n", precio[totalProductos]);

        printf("Continuas incrementando? (s/n): ");
        scanf(" %c", &continuar);
    }

    totalProductos++;
}

double calcularDescuento(double precio) {
    double descuento = 0;

    int i;
    for (i = 1; i <= 3; i++) {
        descuento += (precio * 0.02);
    }

    return precio - descuento;
}

void clasificarProducto(char tipo) {
    switch (tipo) {
        case 'O':
            printf("Es un producto organico.\n");
            break;

        case 'P':
            printf("Es un producto procesado.\n");
            break;

        case 'L':
            printf("Es un producto liquido.\n");
            break;

        default:
            printf("Tipo no valido.\n");
    }
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

void mostrarProductos() {
    int i;
    printf("\n===== Inventario de Productos =====\n");
    for (i = 0; i < totalProductos; i++) {
        printf("Codigo: %d, Precio: %.2f, Tipo: %c\n", codigo[i], precio[i], tipo[i]);
    }
    return;
}

void buscarProducto(int codigoBuscado) {
    int i;
    for (i = 0; i < totalProductos; i++) {
        if (codigo[i] == codigoBuscado) {
            printf("Producto encontrado: Codigo: %d, Precio: %.2f, Tipo: %c\n", codigo[i], precio[i], tipo[i]);
            return;
        }
    }
    printf("Producto con codigo %d no encontrado.\n", codigoBuscado);
}