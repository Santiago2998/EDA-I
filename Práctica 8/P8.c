#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
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
        printf("no hay memoria suficiente para realizar el comando\n");
        return;
    } //Caso lista vacía
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

    printf("Anuncio Insertado");
}

// Función para buscar
struct nodoC* buscarAnuncio(struct nodoC *cabeza, int idBuscado) {
    struct nodoC *actual;

    if (cabeza == NULL) {
        printf("No hay anuncios.\n");
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

// Función para eliminar por valor
void eliminar(struct nodoC **cabeza, int idEliminar) {
    struct nodoC *eliminarNodo;
    struct nodoC *ultimo;

    if (*cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    eliminarNodo = buscarAnuncio(*cabeza, idEliminar);

    if (eliminarNodo == NULL) {
        printf("El anuncio %d no se encontró.\n", idEliminar);
        return;
    }

    // Caso de un solo nodo
    if (eliminarNodo->sig == eliminarNodo) {
        free(eliminarNodo);
        *cabeza = NULL;
        printf("Se eliminó el anuncio %d.\n", idEliminar);
        return;
    }

    // Reenlace de los vecinos
    eliminarNodo->ant->sig = eliminarNodo->sig;
    eliminarNodo->sig->ant = eliminarNodo->ant;

    // Caso de eliminar la cabeza
    if (eliminarNodo == *cabeza) {
        *cabeza = eliminarNodo->sig;
    }

    ultimo = (*cabeza)->ant;
    ultimo->sig = *cabeza;
    (*cabeza)->ant = ultimo;

    free(eliminarNodo);
    printf("Se eliminó el anuncio: %d.\n", idEliminar);
}

void mostrarAnuncioActual(struct nodoC *head){
    struct nodoC *actual = head;

    if (actual == NULL){
        printf("No hay anuncios.\n");
        return;
    }

    printf("\nAnuncio Actual:\n");
    printf("ID: %d\n", actual->id);
    printf("Titulo: %s\n", actual->title);
    printf("Descripcion: %s\n", actual->desc);
}

// Función para mostrar lista mediante sucesores
void siguienteAnuncio(struct nodoC *cabeza) {
    struct nodoC *actual = cabeza;

    if (cabeza == NULL) {
        printf("No hay anuncios.\n");
        return;
    }

    actual = actual->sig;
    mostrarAnuncioActual(actual);
}

// Función para mostrar lista mediante antecesores
void anteriorAnuncio(struct nodoC *cabeza) {
    struct nodoC *actual;

    if (cabeza == NULL) {
        printf("Lista hacia atrás: vacía\n");
        return;
    }

    actual = cabeza->ant;
    mostrarAnuncioActual(actual);
}

void mostrarLista(struct nodoC *head){
    struct nodoC *actual;

    if (head == NULL){
        printf("La lista está vacía.\n");
        return;
    }

    actual = head;
    do{
        mostrarAnuncioActual(actual);
        actual = actual->sig;

    } while (actual != head);

}

// Función para liberar memoria
void liberarLista(struct nodoC **cabeza) {
    struct nodoC *actual;
    struct nodoC *temp;

    if (*cabeza == NULL) {
        return;
    }

    actual = (*cabeza)->sig;

    while (actual != *cabeza) {
        temp = actual->sig;
        free(actual);
        actual = temp;
    }

    free(*cabeza);
    *cabeza = NULL;
}

int main() {
    struct nodoC *anuncios = NULL;
    struct nodoC *encontrado;
    int opcion;

    do
    {
        printf("\n1. Ingresar Anuncio.\n");
        printf("2. Mostrar Anuncio Actual.\n");
        printf("3. Siguiente Anuncio.\n");
        printf("4. Anterior Anuncio.\n");
        printf("5. Eliminar Anuncio.\n");
        printf("6. Salir.\n");
        printf("Selecciona una opcion.\n");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
        case 1: 
            insertEnd(&anuncios, 1, "Loreal", "Shampoo, maquillaje, etc.");
            insertEnd(&anuncios, 2, "Sabritas", "Ruffles, Doritos, Takis");
        break;

        case 2: 
            mostrarAnuncioActual(anuncios);
        break;

        case 3:
            siguienteAnuncio(anuncios);
        break;

        case 4: 
            anteriorAnuncio(anuncios);
            mostrarAnuncioActual(anuncios);
        break;

        case 5: 
            eliminar(&anuncios, 1);
        break;
        
        case 6: 
            printf("Saliendo...\n");
        break;
        
        default:
            printf("error");
        break;
    }

    } while (opcion != 6);
    
    return 0;
}
