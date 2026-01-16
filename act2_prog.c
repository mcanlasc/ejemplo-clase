#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T 12

void menu(){
    printf("\nMENU\n\n");
    printf("1. Jugar\n");
    printf("2. Mejores puntuaciones\n");
    printf("3. Salir\n");
}

void crearTablero(char tab[T][T]){
    for(int i = 0; i < T; i++){
        for(int j = 0; j < T; j++){
            tab[i][j] = '*';
        }
    }
}

void imprimirTablero(char tab[T][T]){
    printf("\n"); 
    for(int i = 0; i < T; i++){
        for(int j = 0; j < T; j++){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

int libre(char tab[T][T],int f, int c){
    return tab[f][c] == '*';
}

void colocarNaves(char tab[T][T], int pos, char nave, int jugador){
    int f, c, ok;
    char orientacion;

    while (1){
        if(jugador == 0){
            f = rand() % T;
            c = rand() % T;
            if(rand() % 2 == 0){
                orientacion = 'H';
            }
            else{
                orientacion = 'V';
            }   
        }
        else{
            imprimirTablero(tab);
            printf("Colocar nave tamaño %d\n", pos);
            printf("Fila (1-12): ");
            scanf("%d", &f);
            printf("Columna (1-12): ");
            scanf("%d", &c);
            printf("Orientacion (H/V): ");
            scanf(" %c", &orientacion);
            f--;
            c--;
        }
        ok = 1;
        if(orientacion == 'H'){
            if(c + pos > T){
                ok = 0;
            }
            if (ok){
                for(int i = 0; i < pos; i++){
                    if(tab[f][c+i] != '*'){
                        ok = 0;
                    }
                }
            }
            if (ok){
                for(int i = 0; i < pos; i++){
                    tab[f][c+i] = nave;
                }
                return;
            }
        }else if(orientacion == 'V'){
            if(f + pos > T){
                ok = 0;
            }
            if (ok){
                for(int i = 0; i < pos; i++){
                    if(tab[f+i][c] != '*'){
                        ok = 0;
                    }
                }
            }
            if (ok){
                for(int i = 0; i < pos; i++){
                    tab[f+i][c] = nave;
                }
                return;
            }
        }
        else{
            ok = 0;
        }
        if(jugador == 1 && !ok){
            printf("No valido. Intentalo otra vez\n\n");
        }
        
    }
}

void colocarBot(char tab[T][T]){
    colocarNaves(tab, 4, 'P', 0);
    colocarNaves(tab, 3, 'C', 0);
    colocarNaves(tab, 3, 'C', 0);
    colocarNaves(tab, 2, 'N', 0);
    colocarNaves(tab, 2, 'N', 0);
    colocarNaves(tab, 2, 'N', 0);
}

void colocarJugador(char tab[T][T]){
    colocarNaves(tab, 4, 'P', 1);
    colocarNaves(tab, 3, 'C', 1);
    colocarNaves(tab, 3, 'C', 1);
    colocarNaves(tab, 2, 'N', 1);
    colocarNaves(tab, 2, 'N', 1);
    colocarNaves(tab, 2, 'N', 1);
}

int main(){
    char tableroJugador[T][T];
    char tableroBot[T][T];
    int opcion = 0;
    srand((unsigned)time(NULL));

    while(opcion != 3){
        menu();
        printf("\nElige una opción: ");
        scanf("%d", &opcion);
        printf("\n");

        switch(opcion){
            case 1:
                crearTablero(tableroBot);
                crearTablero(tableroJugador);
                printf("\nColoca tus naves\n");
                colocarJugador(tableroJugador);
                printf("\nTu tablero");
                imprimirTablero(tableroJugador);

                colocarBot(tableroBot);
                printf("\nTablero del bot");
                imprimirTablero(tableroBot);
                break;

            case 2:
                printf("\nMejores puntuaciones aun no implementado\n");
                break;

            case 3:
                printf("\nSaliendo...\n");
                break;
            
            default:
                printf("\nOpcion invalida\n");
        }
    }
    return 0;

}