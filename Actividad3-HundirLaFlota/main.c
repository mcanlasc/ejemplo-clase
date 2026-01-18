#include <stdio.h>

/* Incluimos directamente el módulo ranking */
#include "act3_loop.c"

// Menú principal del juego
int main(void)
{
    int op;
    do
    {
        printf("\n==== MENU ====\n");
        printf("1. Jugar\n");
        printf("2. Ver mejores puntuaciones\n");
        printf("3. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &op) != 1)
        {
            printf("Entrada invalida.\n");
            return 0;
        }

        switch (op)
        {
        case 1:
            jugarPartida();
            break;
        case 2:
            mostrarMejoresPuntuaciones();
            break;
        case 3:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (op != 3);

    return 0;
}