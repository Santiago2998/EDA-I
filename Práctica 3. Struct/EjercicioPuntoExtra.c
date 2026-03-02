/*
Se hace descifrador de César
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct cifradoC
{
    char textoOriginal[MAX];
    char textoCifrado[MAX];
    int desplazamiento;
};

struct descifradoC {
    char textoCifrado[MAX];
    char textoDescifrado[MAX];
    int desplazamiento;
};

char alfabeto[] = "abcdefghijklmnñopqrstuvwxyz";

//Funcion para encontrar índice de una letra en el alfabeto
int obtenerIndice(char c){
    for (int i = 0; i < 27; i++){
        if (alfabeto[i] == c){
            return i;
        }
    }
    return -1;
}


//Función Cifrado César
void cifrar(struct cifradoC *datos){
    int i;
    for (i = 0; datos->textoOriginal[i] != '\0'; i++){
        char c = tolower(datos->textoOriginal[i]);

        int indice = obtenerIndice(c);


        if (indice != -1){
            int nuevoIndice = (indice + datos->desplazamiento) % 27;
            datos->textoCifrado[i] = alfabeto[nuevoIndice];
        } else {
            datos->textoCifrado[i] = datos->textoOriginal[i];
        }
    }
    datos->textoCifrado[i] = '\0';
}

void descifrar(struct descifradoC *datos){
    int i;
    for (i = 0; datos->textoCifrado[i] != '\0'; i++){
        char c = tolower(datos->textoCifrado[i]);

        int indice = obtenerIndice(c);

        if (indice != -1){
            int nuevoIndice = (indice - datos->desplazamiento + 27) % 27;
            datos->textoDescifrado[i] = alfabeto[nuevoIndice];
        } else {
            datos->textoDescifrado[i] = datos->textoCifrado[i];
        }
    }
    datos->textoDescifrado[i] = '\0';


}

void imprimirDescifrado(){
    struct descifradoC datos;

    printf("\nIngresa el texto a descifrar: ");
    fgets(datos.textoCifrado, MAX, stdin);

    datos.textoCifrado[strcspn(datos.textoCifrado, "\n")] = '\0';

    printf("Ingresa el valor de desplazamiento: ");
    scanf("%d", &datos.desplazamiento);
    getchar();

    descifrar(&datos);

    printf("Texto cifrado: %s\n", datos.textoCifrado);
    printf("Texto Descifrado: %s\n", datos.textoDescifrado);
}

int main(){
    struct cifradoC datos;

    printf("Ingresa el texto a cifrar: ");
    fgets(datos.textoOriginal, MAX, stdin);

    //Se elimina el salto de linea de fgets
    datos.textoOriginal[strcspn(datos.textoOriginal, "\n")] = '\0';

    printf("Ingresa el valor de desplazamiento: ");
    scanf("%d", &datos.desplazamiento);

    cifrar(&datos);

    printf("\nTexto original: %s\n", datos.textoOriginal);
    printf("Texto cifrado: %s\n", datos.textoCifrado);

    int opcion;
    printf("Quiere Descifrar un mensaje? (1 = y, 2 = n)\n");
    scanf("%d", &opcion);
    getchar();
    
    if (opcion == 1){
        imprimirDescifrado();    
    } else if (opcion == 2){
        printf("Finalizando programa....");
    } else {
        printf("Opcion no valida, cerrando programa...");
    }

    return 0;
}
