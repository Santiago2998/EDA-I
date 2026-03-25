#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUCTURAS ---

struct NodoVIP {
    int turno;
    char nombre[50];
    struct NodoVIP *ant;
    struct NodoVIP *sig;
};

struct ColaVIP {
    struct NodoVIP *frente;
    struct NodoVIP *final;
};

struct NodoNormal {
    int turno;
    char nombre[50];
    struct NodoNormal *sig;
};

struct ColaNormal {
    struct NodoNormal *final;
};

// --- FUNCIONES DE APOYO ---

void limpiarSaltoLinea(char *cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] == '\n') {
            cadena[i] = '\0';
        }
        i++;
    }
}

// --- OPERACIONES COLA VIP (COLA DOBLE) ---

void inicializarColaVIP(struct ColaVIP *cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

int colaVIPVacia(struct ColaVIP *cola) {
    return (cola->frente == NULL);
}

void insertarVIP(struct ColaVIP *cola, int turno, char nombre[]) {
    struct NodoVIP *nuevo = (struct NodoVIP *)malloc(sizeof(struct NodoVIP));
    nuevo->turno = turno;
    strcpy(nuevo->nombre, nombre);
    nuevo->sig = NULL;
    nuevo->ant = cola->final;

    if (colaVIPVacia(cola)) {
        cola->frente = nuevo;
    } else {
        cola->final->sig = nuevo;
    }
    cola->final = nuevo;
}

int atenderVIP(struct ColaVIP *cola, int *turno, char nombre[]) {
    if (colaVIPVacia(cola)) return 0;

    struct NodoVIP *temp = cola->frente;
    *turno = temp->turno;
    strcpy(nombre, temp->nombre);

    if (cola->frente == cola->final) {
        cola->frente = NULL;
        cola->final = NULL;
    } else {
        cola->frente = temp->sig;
        cola->frente->ant = NULL;
    }
    free(temp);
    return 1;
}

void mostrarVIP(struct ColaVIP *cola) {
    printf("Usuarios VIP: ");
    if (colaVIPVacia(cola)) {
        printf("Vacia\n");
        return;
    }
    struct NodoVIP *actual = cola->frente;
    while (actual != NULL) {
        printf("Turno: %d, Nombre: %s\n", actual->turno, actual->nombre);
        actual = actual->sig;
    }
}

void liberarVIP(struct ColaVIP *cola) {
    struct NodoVIP *actual = cola->frente;
    while (actual != NULL) {
        struct NodoVIP *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    cola->frente = cola->final = NULL;
}

// --- OPERACIONES COLA NORMAL (COLA CIRCULAR) ---

void inicializarColaNormal(struct ColaNormal *cola) {
    cola->final = NULL;
}

int colaNormalVacia(struct ColaNormal *cola) {
    return (cola->final == NULL);
}

void insertarNormal(struct ColaNormal *cola, int turno, char nombre[]) {
    struct NodoNormal *nuevo = (struct NodoNormal *)malloc(sizeof(struct NodoNormal));
    nuevo->turno = turno;
    strcpy(nuevo->nombre, nombre);

    if (colaNormalVacia(cola)) {
        nuevo->sig = nuevo;
        cola->final = nuevo;
    } else {
        nuevo->sig = cola->final->sig;
        cola->final->sig = nuevo;
        cola->final = nuevo;
    }
}

int atenderNormal(struct ColaNormal *cola, int *turno, char nombre[]) {
    if (colaNormalVacia(cola)) return 0;

    struct NodoNormal *frente = cola->final->sig;
    *turno = frente->turno;
    strcpy(nombre, frente->nombre);

    if (frente == cola->final) { // Solo un elemento
        cola->final = NULL;
    } else {
        cola->final->sig = frente->sig;
    }
    free(frente);
    return 1;
}

void mostrarNormal(struct ColaNormal *cola) {
    printf("Usuarios Normales: ");
    if (colaNormalVacia(cola)) {
        printf("Vacia\n");
        return;
    }
    struct NodoNormal *primero = cola->final->sig;
    struct NodoNormal *actual = primero;
    do {
        printf("Turno: %d, Nombre: %s\n", actual->turno, actual->nombre);
        actual = actual->sig;
    } while (actual != primero);
}

void liberarNormal(struct ColaNormal *cola) {
    if (colaNormalVacia(cola)) return;
    struct NodoNormal *actual = cola->final->sig;
    cola->final->sig = NULL; // Romper circularidad para liberar
    while (actual != NULL) {
        struct NodoNormal *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    cola->final = NULL;
}

// --- ATENCIÓN MIXTA ---

void atenderSiguiente(struct ColaVIP *vip, struct ColaNormal *normal) {
    int turno;
    char nombre[50];

    if (atenderVIP(vip, &turno, nombre)) {
        printf("\nSe atiende a usuario VIP:\n");
        printf(" Turno VIP %d - %s\n", turno, nombre);
    } else if (atenderNormal(normal, &turno, nombre)) {
        printf("\nSe atiende a usuario normal:\n");
        printf(" Turno normal %d - %s\n", turno, nombre);
    } else {
        printf("\nNo hay usuarios en espera.\n");
    }
}

// --- MAIN ---

int main() {
    struct ColaVIP colaVIP;
    struct ColaNormal colaNormal;
    int opcion, contadorVIP = 1, contadorNormal = 1;
    char nombre[50];

    inicializarColaVIP(&colaVIP);
    inicializarColaNormal(&colaNormal);

    do {
        printf("\n=== SISTEMA MIXTO DE ATENCION ===\n");
        printf("1. Registrar usuario VIP\n");
        printf("2. Registrar usuario Normal\n");
        printf("3. Atender siguiente usuario\n");
        printf("4. Mostrar colas\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) break;
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del usuario VIP: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiarSaltoLinea(nombre);
                insertarVIP(&colaVIP, contadorVIP++, nombre);
                printf("Usuario VIP registrado correctamente.\n");
                break;
            case 2:
                printf("Ingrese el nombre del usuario normal: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiarSaltoLinea(nombre);
                insertarNormal(&colaNormal, contadorNormal++, nombre);
                printf("Usuario normal registrado correctamente.\n");
                break;
            case 3:
                atenderSiguiente(&colaVIP, &colaNormal);
                break;
            case 4:
                printf("\n--- ESTADO ACTUAL DE LAS COLAS ---\n");
                mostrarVIP(&colaVIP);
                mostrarNormal(&colaNormal);
                break;
            case 5:
                printf("Saliendo y liberando memoria...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);

    liberarVIP(&colaVIP);
    liberarNormal(&colaNormal);
    return 0;
}