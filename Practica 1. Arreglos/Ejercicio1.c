/*
Capturar e imprimir 10 números enteros 

--Planteamiento del problema--
Crear una aplicación CLI que solicite al usuario 10 números enteros, los acumule en un arreglo
y los imprima en el mismo orden que fueron capturados.

--Pseudocódigo (Entra en Desarrollo)--
1. Se define el arreglo de tamaño 10 
2. Se define estructura 'for(i=0; i<=9; i++)'
2.1. Se solicitan los 10 números
3. Se define estructura 'for(j=0; j<=9; j++)'
3.1. Se imprime número con base en posición

*/
#include <stdio.h>

int main(){
    int numeros[10];
    int i;
    
    printf("Ingresa 10 numeros: \n");
    for(i = 0; i <= 9; i++){
        printf("Numero: %d\n", i+1);
        scanf("%d", &numeros[i]);
    }
    printf("\nNumeros capturados (en orden de captura): \n");
    for(i = 0; i <= 9; i++){
        printf("%d\n", numeros[i]);
    }

    return 0;
}