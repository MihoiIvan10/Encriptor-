#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


/*  --------------------------------------------------------------------------------------------------------------  
    Encriptador de la forma x -> nx + k mod (36) donde tenemos como diccionario abcdefghijklmnopqrstuvwxyz0123456789
    Etrada:
        Texto, n, k
	Objetivo: 
		Texto ecriptado 
----------------------------------------------------------------------------------------------------------------------*/


#define MAX_LENGTH 100

char diccionario[] = "abcdefghijklmnopqrstuvwxyz0123456789";

const double raiz = 2;
char mensaje[MAX_LENGTH];


void obtenerMensaje();
int numCongruente(int pos, int n);
void cifrarMensaje(char *mensaje, int n, int k);
long potencia(long num, long exp);

int main() {
    int n = 0; // Inicializa n
    int k = 0; // Inicializa k

    printf("Ingresa el valor de n: ");
    scanf("%d", &n);
    printf("Ingresa el valor de k: ");
    scanf("%d", &k);
    getchar(); // Limpia el buffer del salto de línea después de scanf

    obtenerMensaje();

    cifrarMensaje(mensaje, n,k);
    printf("Mensaje cifrado: %s\n", mensaje);

    return 0;
}


void obtenerMensaje() {
    printf("Ingresa el mensaje: ");
    fgets(mensaje, sizeof(mensaje), stdin);
    mensaje[strcspn(mensaje, "\n")] = '\0'; 
}

// Funcion que checa con que es congruente 
int numCongruente(int pos, int n){
    for(int i=0; i<n; i++){
        if(pos==i){
            return i;
        }
    }
    return -1;
}


//Calcula la potencia para numeros grandes ya que al calcular 2^32 se hace 0
long potencia(long num, long exp){
    if (exp <= 0){
        return 1;
    }
    else{
        return num * potencia(num, exp - 1);
    }
}


//Funcion que cifra el mensaje
void cifrarMensaje(char *mensaje, int n, int k) {
    int diccionario_length = strlen(diccionario) + 1;
    for (int i = 0; i < strlen(mensaje); i++) {
        char c = mensaje[i];
        bool esMayuscula = isupper(c);
        int pos = strchr(diccionario, tolower(c)) - diccionario + 1;
        if (isalnum(c)){
            int dv = (pos * n) + k;

            pos = dv % (diccionario_length-1);

            if(pos<0) pos += diccionario_length - 1;

            int aux1 = numCongruente(pos,diccionario_length);
            
            long aux2 = potencia(raiz,aux1);
            int aux = aux2 % (diccionario_length);

            int aux3 = numCongruente(aux,diccionario_length);
            if(esMayuscula){                    // Aqui checa si la posicion i era mayuscula
                mensaje[i] = toupper(diccionario[aux3-1]);   // Si lo era esta convierte en mayuscula al texto encripado 
            }
            else{
                mensaje[i] = diccionario[aux-1];
            }

            n = k;
            k = aux3;

        }
    }
}
