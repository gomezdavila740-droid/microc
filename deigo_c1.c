#include <stdio.h>

int main() {

    int N;
    int suma = 0;
    int impar = 1;
    int i;

    printf("INGRESE UN NUMERO ENTERO POSITIVO: ");
    
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 0;
    }

    for (i = 0; i < N; i++) {
        suma += impar;
        impar += 2;
    }

    printf("El cuadrado de %d es: %d\n", N, suma);

    return 0;
}