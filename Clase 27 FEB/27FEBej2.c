#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arreglo1, *arreglo2, num, cont; 

    printf("Cuantos elementos tiene el arreglo?\n");
    scanf("%d", &num);
    arreglo1 = (int *)malloc (num * sizeof(int));
    if (arreglo1 != NULL){
        for (cont = 0; cont < num; cont++){
            printf("Inserta el elemento %d del arreglo.\n", cont+1);
            scanf("%d", (arreglo1+cont));
        }
        printf("Arreglo insertado:\n\t[");
        for (cont = 0; cont < num; cont++){
            printf("\t%d", *(arreglo1+cont));
        }
        printf("\t]\n");
        printf("Se incrementa el tamaño del arreglo al doble.\n");
        num *= 2;
        arreglo2 = (int *)realloc (arreglo1, num*sizeof(int));
        if (arreglo2 != NULL){
            arreglo1 = arreglo2;
            for (; cont < num; cont++){
                printf("Inserta el elemento %d del arreglo.\n", cont+1);
                scanf("%d", (arreglo2+cont));
            }
            printf("Arreglo insertado:\n\t[");
            for (cont = 0; cont < num; cont++){
                printf("\t%d", *(arreglo2+cont));
            }
            printf("\t]\n");
        }
        free(arreglo1);

    }

    return 0;
}