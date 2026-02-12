/*
Encontrar el mayor y el menor en un arreglo

--Planteamiento del problema--
Vamos a crear una aplicación CLI que pida al usuario un valor n (rango de 1 a 100)
que capture los n valores y finalmente pueda determinar el valor mayor y el valor menor del arreglo

--Pseudocódigo--
1. Declarar el arreglo con el valor n definido
2. Solicitar los n números con estructura de control
3. Se recorre el arreglo desde 1 hasta n-1
3.1 Se compara si arr[i]>max; si arr[i]<min
3.2 Si es caso 1, entonces max=arr[i]
3.3 Si es caso 2, entonces min=arr[i]
4. Se imprimen valores

*/
#include <stdio.h>

int main(){
    int numeros[100];
    int n, i;
    int max, min;
    
    printf("Dame el valor de n (en un rango de 0 a 100): ");
    scanf("%d", &n);

    while(n < 1 || n > 100){
        printf("Valor de n invalido...Ingresa un valor entre 1 y 100: ");
        scanf("%d", &n);
    }

    printf("Ingresa %d numeros enteros: \n", n);

    for(i = 0; i < n; i++){
        printf("Numero %d", i+1);
        scanf("%d", &numeros[i]);
    }

    max = numeros[0];
    min = numeros[0];

    for(i = 1; i < n; i++){
        if(numeros[i] > max){
            max = numeros[i];
        }
        if (numeros[i] < min){
            min = numeros[i];
        }
    }

    printf("\nValor mayor = %d\n", max);
    printf("\nValor menor = %d\n", min);

    return 0;
}