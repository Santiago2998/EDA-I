#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Vigenere{
    char textoOriginal[MAX];
    char textCifrado[MAX];
    char clave[MAX];
};

char alfabeto[] = "abcdefghijklmnñopqrstuvwxyz";

//Función para obtener índice de una letra
int obtenerIndice(char c){
    for (int i = 0; i < 27; i++){ 
        if (alfabeto[i] == c){
            return i;
        }
    }

    return -1;
}

//Función para cifrar con criterio Vigenère
void cifrar(struct Vigenere *datos){
    int i, j = 0;

    int lenTexto = strlen(datos->textoOriginal);
    int lenClave = strlen(datos->clave);

    for (i = 0; i < lenTexto; i++){
        char letraTexto = tolower(datos->textoOriginal[i]);

        int indiceTexto = obtenerIndice(letraTexto);

        if (indiceTexto != -1){
            char letraClave = tolower(datos->clave[j % lenClave]);
            int indiceClave = obtenerIndice(letraClave);

            int nuevoIndice = (indiceTexto/*Xi*/ + indiceClave/*Ki*/) % 27;

            datos->textCifrado[i] = alfabeto[nuevoIndice];

            j++; //Quien lleva avance de cifrado
        } else {
            //Se conserva espacios y símbolos
            datos->textCifrado[i] = datos->textoOriginal[i];
        }
    }
    datos->textCifrado[i] = '\0';
}

int main(){
    struct Vigenere datos;

    printf("Ingrese el texto a cifrar: ");
    fgets(datos.textoOriginal, MAX, stdin);
    datos.textoOriginal[strcspn(datos.textoOriginal, "\n")] = '\0';

    printf("Ingresa la clave: ");
    fgets(datos.clave, MAX, stdin);
    datos.clave[strcspn(datos.clave, "\n")] = '\0';

    cifrar(&datos);

    printf("\nTexto original: %s\n", datos.textoOriginal);
    printf("Clave: %s\n", datos.clave);
    printf("Texto Cifrado : %s\n", datos.textCifrado);

    return 0;
}