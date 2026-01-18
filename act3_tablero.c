//Autores: Raul Mateo Sanguino, Agoney Hernández Trujillo, Marc Anjelo Canlas Castañeda
//Proposito: Crear tablero, colocar barcos manualmente, mostrar tablero. Usado para act3_loop

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T 12

// Inicializa el tablero con celdas vacias
void crearTablero(char tab[T][T]){
    for(int i = 0; i < T; i++){
        for(int j = 0; j < T; j++){
            tab[i][j] = '*';
        }
    }
}

//Muestra el tablero en pantalla con filas y columnas
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

//Coloca las naves para el CPU y permite al jugador poner sus naves manualmente
void colocarNaves(char tab[T][T], int pos, char nave, int jugador){
    int f, c, ok;
    char orientacion;

    while (1){
        if(jugador == 0){ //Elige la orientación al azar para el CPU
            f = rand() % T;
            c = rand() % T;
            if(rand() % 2 == 0){
                orientacion = 'H';
            }
            else{
                orientacion = 'V';
            }   
        }
        else{ //Pide donde colocar las naves
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
        if(orientacion == 'H'){ //Control de error (Si la nave esta fuera del tablero)
            if(c + pos > T){
                ok = 0;
            }
            if (ok){ //Control de error (Si ya existe un barco en esa posicion)
                for(int i = 0; i < pos; i++){
                    if(tab[f][c+i] != '*'){
                        ok = 0;
                    }
                }
            }
            if (ok){ //Coloca la nave
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

//Coloca todas las naves del bot
void colocarBot(char tab[T][T]){ 
    colocarNaves(tab, 4, 'P', 0);
    colocarNaves(tab, 3, 'C', 0);
    colocarNaves(tab, 3, 'C', 0);
    colocarNaves(tab, 2, 'N', 0);
    colocarNaves(tab, 2, 'N', 0);
    colocarNaves(tab, 2, 'N', 0);
}

//Coloca todas las naves del jugador
void colocarJugador(char tab[T][T]){
    colocarNaves(tab, 4, 'P', 1);
    colocarNaves(tab, 3, 'C', 1);
    colocarNaves(tab, 3, 'C', 1);
    colocarNaves(tab, 2, 'N', 1);
    colocarNaves(tab, 2, 'N', 1);
    colocarNaves(tab, 2, 'N', 1);
}