#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 255

struct nodoC {
    int id;
    char title[100];
    char desc[MAX];
    struct nodoC *sig;
    struct nodoC *ant;
};

struct nodoC *crearNodo(int nid, char ntitle[], char ndesc[]){
    struct nodoC *nuevo = (struct nodoC *)malloc(sizeof(struct nodoC));
    if (nuevo == NULL){
        printf("Error de memoria.\n");
        return NULL;
    }
    nuevo->id = nid;
    strcpy(nuevo->title, ntitle);
    strcpy(nuevo->desc, ndesc);
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

void insertEnd(struct nodoC **cabeza, int nid, char ntitle[], char ndesc[]){
    struct nodoC *nuevo = crearNodo(nid, ntitle, ndesc);
    struct nodoC *ultimo;

    if (nuevo == NULL){
        return;
    }

    if (*cabeza == NULL){
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        *cabeza = nuevo;
        return;
    }

    ultimo = (*cabeza)->ant;

    nuevo->sig = *cabeza;
    nuevo->ant = ultimo;

    ultimo->sig = nuevo;
    (*cabeza)->ant = nuevo;

    printf("Anuncio insertado.\n");
}

struct nodoC* buscarAnuncio(struct nodoC *cabeza, int idBuscado) {
    struct nodoC *actual;

    if (cabeza == NULL) {
        return NULL;
    }

    actual = cabeza;

    do {
        if (actual->id == idBuscado) {
            return actual;
        }
        actual = actual->sig;
    } while (actual != cabeza);

    return NULL;
}

void eliminar(struct nodoC **cabeza, int idEliminar) {
    struct nodoC *eliminarNodo;

    if (*cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    eliminarNodo = buscarAnuncio(*cabeza, idEliminar);

    if (eliminarNodo == NULL) {
        printf("El anuncio %d no se encontró.\n", idEliminar);
        return;
    }

    if (eliminarNodo->sig == eliminarNodo) {
        free(eliminarNodo);
        *cabeza = NULL;
        printf("Se eliminó el anuncio %d.\n", idEliminar);
        return;
    }

    eliminarNodo->ant->sig = eliminarNodo->sig;
    eliminarNodo->sig->ant = eliminarNodo->ant;

    if (eliminarNodo == *cabeza) {
        *cabeza = eliminarNodo->sig;
    }

    free(eliminarNodo);
    printf("Se eliminó el anuncio %d.\n", idEliminar);
}

void mostrarAnuncioActual(struct nodoC *actual){
    if (actual == NULL){
        printf("No hay anuncios.\n");
        return;
    }

    printf("\nAnuncio Actual:\n");
    printf("ID: %d\n", actual->id);
    printf("Titulo: %s\n", actual->title);
    printf("Descripcion: %s\n", actual->desc);
}

int main() {
    struct nodoC *anuncios = NULL;
    struct nodoC *actual = NULL;
    int opcion;

    do {
        printf("\n1. Ingresar Anuncio.\n");
        printf("2. Mostrar Anuncio Actual.\n");
        printf("3. Siguiente Anuncio.\n");
        printf("4. Anterior Anuncio.\n");
        printf("5. Eliminar Anuncio.\n");
        printf("6. Salir.\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
        case 1: 
            insertEnd(&anuncios, 1, "Loreal", "Shampoo, maquillaje, etc.");
            insertEnd(&anuncios, 2, "Sabritas", "Ruffles, Doritos, Takis");

            if (actual == NULL)
                actual = anuncios;
        break;

        case 2: 
            mostrarAnuncioActual(actual);
        break;

        case 3:
            if (actual != NULL)
                actual = actual->sig;
            mostrarAnuncioActual(actual);
        break;

        case 4: 
            if (actual != NULL)
                actual = actual->ant;
            mostrarAnuncioActual(actual);
        break;

        case 5: 
            eliminar(&anuncios, 1);
            actual = anuncios;
        break;
        
        case 6: 
            printf("Saliendo...\n");
        break;
        
        default:
            printf("Opcion invalida.\n");
        break;
        }

    } while (opcion != 6);
    
    return 0;
}
