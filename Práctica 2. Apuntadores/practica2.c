

#include <stdio.h>
#include <string.h>

//funcion para intercambiar dos bytes usando apuntadores
void swapByte(unsigned char *x, unsigned char *y) {
    unsigned char temp = *x;
    *x= *y;
    *y= temp;
}
    //funcion digestiva simulando MD5

    void md5Simulado (const char *texto, unsigned char digest[16]) {
        //Estados internos 
        unsigned char A = 0x12;
        unsigned char B = 0x34;
        unsigned char C = 0x56;
        unsigned char D = 0x78;
        
        //Se recorre la cadena con apuntador
        const char *p = texto;

        while (*p != '\0') {
            unsigned char x = (unsigned char) (*p);

            //proceso de digestion simple
            A = (unsigned char) (A + x + B);
            B = (unsigned char) (B ^ x);
            C = (unsigned char) (C + (unsigned char) (x*3)+D);
            D = (unsigned char) (D ^ (unsigned char) (x+A));
            
            //Mezcla sencilla de bytes
            if ((x % 2) ==0) {
                swapByte(&A, &C);
            } 
            else {
                swapByte(&B, &D);
            }
            p++; //Avanza el apuntador
        }

        //Se contruyen los 16 bytes a partir de los estados iniciales
        //Se hace repeticion y combinacion simples
        for (int i =0; i<16; i++) {
            if ( i% 4 ==0) digest[i] = (unsigned char) (A +i);
            if ( i % 4 ==1) digest[i] = (unsigned char) (B +i);
            if ( i % 4 ==2) digest[i] = (unsigned char) (C ^ i);
            if ( i % 4 ==3) digest[i] = (unsigned char) (D ^ (A+i));
        }
    }

    //Funcion para mostrar los 16 bytes en 32 caracteres hexadecimales
    void imprimirHex(const unsigned char *digest, int n) {
        const unsigned char *p = digest;
        for (int i=0; i <n;i++) {
            printf("%02x", *p);
        }
        printf("\n");
    }
    //main
    int main () {
        char texto[256];

        printf("Ingresa un mensaje: ");
        if (!fgets(texto, sizeof(texto), stdin)) {
            printf("Error al leer la entrada...\n");
            return 1;
        }
    
//quitar salto de linea
    size_t n=strlen(texto);
if (n>0&& texto [n-1]=='\n') {
    texto[n-1]='\0';
}
unsigned char digest [16];
md5Simulado(texto, digest);

    printf("Hash tipo MD5 (simulado): ");
imprimirHex (digest, 16);
        return 0;
    }
    
