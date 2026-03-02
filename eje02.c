/*
Actividad 4.7.6.2
*/

#include <stdio.h>
#include <string.h>

int main() {

    char mensaje[50];

    int valor;
    int ultimo = 0;
    int mayor = -1;
    int menor = 100;
    int suma = 0;
    int contador = 0;

    while (1) {

        if (fgets(mensaje, sizeof(mensaje), stdin) == NULL) {
            break;
        }

        if (sscanf(mensaje, "{ 'caudal': %d }", &valor) == 1) {

            if (valor >= 0 && valor <= 99) {

                ultimo = valor;

                if (mayor == -1 || valor > mayor) {
                    mayor = valor;
                }

                if (valor < menor) {
                    menor = valor;
                }

                suma += valor;
                contador++;

                printf("{ 'ultimo': %d, 'mayor': %d, 'menor': %d, 'promedio': %.2f }\n",
                       ultimo, mayor, menor, (float)suma / contador);
            }
        }
    }

    return 0;
}