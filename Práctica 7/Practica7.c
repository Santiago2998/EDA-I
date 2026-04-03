#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100

struct Cancion {
    char titulo[MAX_TITULO];
    struct Cancion* siguiente;
};

// Función para insertar una canción al final de la lista
void insertarCancion(struct Cancion** lista, char titulo[]) {
    struct Cancion* nueva = (struct Cancion*)malloc(sizeof(struct Cancion));
    if (nueva == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }

    strcpy(nueva->titulo, titulo);

    if (*lista == NULL) {
        nueva->siguiente = nueva;
        *lista = nueva;
    } else {
        struct Cancion* actual = *lista;
        while (actual->siguiente != *lista) {
            actual = actual->siguiente;
        }
        actual->siguiente = nueva;
        nueva->siguiente = *lista;
    }

    printf("Cancion \"%s\" agregada a la lista.\n", titulo);
}

// Función para buscar una canción por título
struct Cancion* buscarCancion(struct Cancion* lista, char titulo[]) {
    if (lista == NULL) {
        return NULL;
    }

    struct Cancion* actual = lista;

    do {
        if (strcmp(actual->titulo, titulo) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != lista);

    return NULL;
}

// Función para eliminar canción por título
void eliminarCancion(struct Cancion** lista, struct Cancion** reproduciendo, char titulo[]) {
    if (*lista == NULL) {
        printf("La lista de reproducción está vacía.\n");
        return;
    }

    struct Cancion* actual = *lista;
    struct Cancion* anterior = NULL;

    do {
        if (strcmp(actual->titulo, titulo) == 0) {
            // Caso en que solo hay una canción
            if (actual->siguiente == actual) {
                if (*reproduciendo == actual) {
                    *reproduciendo == NULL;
                }
                free(actual);
                *lista = NULL;
                printf("Cancion \"%s\" eliminada.\n", titulo);
                return;
            }

            // Caso de eliminar la cabeza de la lista de más de un elemento
            if (actual == *lista) {
                struct Cancion* ultimo = *lista;
                while (ultimo->siguiente != *lista) {
                    ultimo = ultimo->siguiente;
                }

                if (*reproduciendo == actual) {
                    *reproduciendo = actual->siguiente;
                }
                *lista = actual->siguiente;
                ultimo->siguiente = *lista;
                free(actual);
                printf("Cancion \"%s\" eliminada.\n", titulo);
                return;
            }

            // Caso general
            anterior->siguiente = actual->siguiente;

            if (*reproduciendo == actual) {
                *reproduciendo = actual->siguiente;
            }
            free(actual);
            printf("Cancion \"%s\" eliminada.\n", titulo);
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    } while (actual != *lista);

    printf("La canción \"%s\" no se encontró en la lista.\n", titulo);
}

// Función para iniciar reproducción
void empezarReproduccion(struct Cancion* lista, struct Cancion** reproduciendo) {
    if (lista == NULL) {
        printf("No hay canciones en la lista de reproducción.\n");
        *reproduciendo = NULL;
        return;
    }

    *reproduciendo = lista;
    printf("Reproduciendo: %s\n",(*reproduciendo)->titulo);
}

// Función para pasar a siguiente canción

void siguienteCancion(struct Cancion** reproduciendo) {
    if (*reproduciendo == NULL) {
        printf("No hay ninguna canción en reproducción.\n");
        return;
    }

    *reproduciendo = (*reproduciendo)->siguiente;
    printf("Ahora suena: %s\n", (*reproduciendo)->titulo);
}

// Función para mostrar estructura Lista

void mostrarLista(struct Cancion* lista) {
    if (lista == NULL) {
        printf("La lista de reproducción está vacía.\n");
        return;
    }

    struct Cancion* actual = lista;
    printf("\n--- Lista de reproducción: ---\n");

    do {
        printf("- %s\n", actual->titulo);
        actual = actual->siguiente;
    } while (actual != lista);
}

// Para liberar memoria de toda la estructura

void liberarLista(struct Cancion** lista) {
    if (*lista == NULL) {
        return;
    }

    struct Cancion* actual = (*lista)->siguiente;
    while (actual != *lista) {
        struct Cancion* temp = actual;
        actual = actual->siguiente;
        free(actual);
    }

    free(*lista);
    *lista = NULL;
}

int main() {
    struct Cancion* lista = NULL;
    struct Cancion* reproduciendo = NULL;

    char titulo[MAX_TITULO];

    int opcion = 0;

    do{
        printf("\n======SIMULADOR DE REPRODUCTOR DE ARCHIVOS DE AUDIO=======\n");
        printf("1. Insertar canciones a la lista de reproducción.\n");
        printf("2. Buscar canciones por nombre.\n");
        printf("3. Eliminar canciones existentes.\n");
        printf("4. Iniciar la reproducci ́on de una canción.\n");
        printf("5. Avanzar a la siguiente canción disponible.\n");
        printf("6. Salir.\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion){
            case 1:
                printf("Ingresa el título de la canción: ");
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                insertarCancion(&lista, titulo);
                break;
            
                case 2:
                    printf("Ingresa el título a buscar: ");
                    fgets(titulo, MAX_TITULO, stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    if (buscarCancion(lista, titulo) != NULL) {
                        printf("La canción \"%s\" si está en la lista.\n", titulo);
                    } else {
                        printf("La canción \"%s\" no está en la lista.\n", titulo);
                    }
                    break;

                case 3:
                    printf("Ingresa el título a eliminar: ");
                    fgets(titulo, MAX_TITULO, stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    eliminarCancion(&lista, &reproduciendo, titulo);
                    break;
                
                case 4:
                    empezarReproduccion(lista, &reproduciendo);
                    break;

                case 5:
                    siguienteCancion(&reproduciendo);
                    mostrarLista(lista);
                    break;

                case 6:
                    printf("--- Fin de la ejecución ---\n");
                    break;

                default:
                printf("Error, opción no válida.\n");
        }
    }while(opcion != 5);
    
    return 0;
}
