/*
Suma + Promedio de n Números

--Planteamiento del problema--
Vamos a crear una aplicación CLI, que pida al usuario un número entero (con rango 1<=n<=100).
Luego debe solicitar los números enteros, guardarlos en un arreglo, calcular la suma de todos los elementos para después calcular el promedio

--Pseudocódigo--
1. Declarar el arreglo con el valor n definido
2. Solicitar los n Números con estructura de control de ciclo
2.1 Se hace la suma con el valor registrado en el arreglo
3. Calculo del promdeio promedio=suma/n
4. Se imprime el resultado
*/
#include <stdio.h>

int main(){
    int numeros[100];
    int n, i, suma;
    double promedio;

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
        suma += numeros[i];
    }
    promedio = suma / n;
    printf("\nEl promedio es: %lf", promedio);

    return 0;
}