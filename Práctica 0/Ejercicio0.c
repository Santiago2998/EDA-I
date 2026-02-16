/*
Evalucación Semanal cero

Crea un programa que haga lo siguiente:
1. Defina dos variables enteras
2. Permita sumar
3. Permita multiplicar
4. Permita operación de módulo

*/
#include <stdio.h>
int main(){
    int x = 5, y = 8, suma, multiplicacion, modulo;
    suma = x + y;
    multiplicacion = x * y;
    modulo = x % y;
    printf("Los resultados son: \nSuma: %d\nMultiplicacion: %d\nModulo: %d\n", suma, multiplicacion, modulo);

    return 0;
}