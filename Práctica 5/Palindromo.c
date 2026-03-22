#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//NODO
struct Nodo{
    char texto;
    struct Nodo *next;
};

//Declarando COLA

struct Cola{
    struct Nodo *head;
    struct Nodo *tail;
};

void inicializar(struct Cola *p){
    p->head = NULL;
    p->tail = NULL;
};

void encolar(struct Cola *ap, char letra){
    struct Nodo *nuevo;
    nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

    if (nuevo == NULL){
        printf("Error de memoria.\n");
        return;
    }

    nuevo->texto = letra;
    nuevo->next = NULL;

    if (ap->head == NULL){
        ap->head = nuevo;
        ap->tail = nuevo;
    } else {
        ap->tail->next = nuevo;
        ap->tail = nuevo;
    }
}

char desencolar(struct Cola *ap){
    struct Nodo *temp;
    char caracter;

    temp = ap->head;
    caracter = temp->texto;

    ap->head = temp->next;

    free(temp);
    return caracter;
}

//Declarando PILA

void push(struct Nodo **top, char caracter){
    struct Nodo *nuevo;
    nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

    if (nuevo == NULL){
        printf("Error de memoria.\n");
        return;
    }

    nuevo->texto = caracter;
    nuevo->next = *top;
    *top = nuevo;
}

char pop(struct Nodo **top){
    struct Nodo *temp;
    char caracter;

    temp = *top;
    caracter = temp->texto;

    *top = temp->next;

    free(temp);
    return caracter;
}

//MAIN

int main(){
    struct Nodo *llenado = NULL;
    struct Cola llenar;
    char palabra[100];

    inicializar(&llenar);

   printf("Dame una palabra: ");
   fgets(palabra, 100, stdin);
   palabra[strcspn(palabra, "\n")] = '\0';

   for (int i = 0; palabra[i] != '\0'; i++){
        char letra;
        letra = tolower(palabra[i]);

        push(&llenado, letra);
        encolar(&llenar, letra);
   }

   int esPalindromo = 1;

   for (int i = 0; palabra[i] != '\0'; i++){
        char caracter1;
        char caracter2;

        caracter1 = pop(&llenado);
        caracter2 = desencolar(&llenar);

        if (caracter1 != caracter2){
            esPalindromo = 0;
            break;
        }
   }

   if (esPalindromo == 1){
        printf("La palabra '%s' es un palindormo.", palabra);
   } else{
        printf("La palabra '%s' no es palindromo", palabra);
   }

   return 0;

}
