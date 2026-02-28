/*
<stdlib.h>  => Permite usar funciones de memoria dinámica

*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arreglo, num, cont;

    printf("Cuantos elementos tiene el arreglo?\n");
    scanf("%d", &num);
    arreglo = (int *)calloc(num, sizeof(int));
    //                 Este espacio es el tamaño dinámico
    //  La variable arreglo se encuentra en el stack y tiene un enlace con Heap para que esto vaya creciendo

    if (arreglo != NULL){
        printf("Arreglo reservado dinamicamente: \n\t[");
        for (cont = 0; cont < num; cont++){
            printf("\t%d", *(arreglo + cont));
        }
        printf("\t]\n");
        printf("Se libera el espacio reservado. \n");
        free(arreglo);
    }

    return 0;
}