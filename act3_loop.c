//Autores: Raul Mateo Sanguino, Agoney Hernández Trujillo, Marc Anjelo Canlas Castañeda
//Proposito: Control principal del juego: menu principal, logica del juego, integración del tablero.c y ranking.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "act3_ranking.c"
#include "act3_tablero.c"

#define N 12

#define PORTAVIONES 1
#define CRUCEROS    2
#define PATRULLERAS 3

#define TAM_PORTA 4
#define TAM_CRUC  3
#define TAM_PATR  2

#define AGUA         0
#define BARCO        1
#define TOCADO       2
#define DISPARO_AGUA 3

int dentro(int f, int c) {
    return f >= 0 && f < N && c >= 0 && c < N;
}

void init_int_board(int b[N][N], int val) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            b[i][j] = val;
}

void init_char_board(char b[N][N], char val) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            b[i][j] = val;
}

void imprimir_tablero_disparos(const char t[N][N]) {
    printf("\n   ");
    for (int j = 0; j < N; j++) printf("%2d", j);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%2d ", i);
        for (int j = 0; j < N; j++) {
            printf("%2c", t[i][j]);   // '*', 'X', 'A'
        }
        printf("\n");
    }
}

void imprimir_tablero_propio(const int b[N][N]) {
    // Muestra tus barcos como 'B', impactos como 'X', agua disparada como 'A', y desconocido como '.'
    printf("\n   ");
    for (int j = 0; j < N; j++) printf("%2d", j);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%2d ", i);
        for (int j = 0; j < N; j++) {
            char ch = '.';
            if (b[i][j] == BARCO) ch = 'B';
            else if (b[i][j] == TOCADO) ch = 'X';
            else if (b[i][j] == DISPARO_AGUA) ch = 'A';
            printf("%2c", ch);
        }
        printf("\n");
    }
}

int cabe_y_libre(const int b[N][N], int f, int c, int tam, int horizontal) {
    for (int k = 0; k < tam; k++) {
        int ff = f + (horizontal ? 0 : k);
        int cc = c + (horizontal ? k : 0);
        if (!dentro(ff, cc)) return 0;
        if (b[ff][cc] != AGUA) return 0;
    }
    return 1;
}

void poner_barco(int b[N][N], int f, int c, int tam, int horizontal) {
    for (int k = 0; k < tam; k++) {
        int ff = f + (horizontal ? 0 : k);
        int cc = c + (horizontal ? k : 0);
        b[ff][cc] = BARCO;
    }
}

void colocar_flota_aleatoria(int b[N][N]) {
    int colocados = 0;

    // Portaviones (4) x1
    while (colocados < PORTAVIONES) {
        int f = rand() % N, c = rand() % N;
        int h = rand() % 2;
        if (cabe_y_libre(b, f, c, TAM_PORTA, h)) {
            poner_barco(b, f, c, TAM_PORTA, h);
            colocados++;
        }
    }

    // Cruceros (3) x2
    colocados = 0;
    while (colocados < CRUCEROS) {
        int f = rand() % N, c = rand() % N;
        int h = rand() % 2;
        if (cabe_y_libre(b, f, c, TAM_CRUC, h)) {
            poner_barco(b, f, c, TAM_CRUC, h);
            colocados++;
        }
    }

    // Patrulleras (2) x3
    colocados = 0;
    while (colocados < PATRULLERAS) {
        int f = rand() % N, c = rand() % N;
        int h = rand() % 2;
        if (cabe_y_libre(b, f, c, TAM_PATR, h)) {
            poner_barco(b, f, c, TAM_PATR, h);
            colocados++;
        }
    }
}

int total_celdas_barco(void) {
    return PORTAVIONES * TAM_PORTA + CRUCEROS * TAM_CRUC + PATRULLERAS * TAM_PATR; // 16
}

// Devuelve 'X' si acierta, 'A' si falla.
// Si ya se disparó ahí, devuelve 0 (para que puedas repetir turno o perderlo).
char disparar(int enemigo[N][N], char visible[N][N], int f, int c, int *celdas_restantes) {
    if (visible[f][c] == 'X' || visible[f][c] == 'A') return 0;

    if (enemigo[f][c] == BARCO) {
        enemigo[f][c] = TOCADO;
        visible[f][c] = 'X';
        (*celdas_restantes)--;
        return 'X';
    } else {
        if (enemigo[f][c] == AGUA) enemigo[f][c] = DISPARO_AGUA;
        visible[f][c] = 'A';
        return 'A';
    }
}

void cpu_elegir_disparo(const char visible_jugador[N][N], int *f, int *c) {
    while (1) {
        int rr = rand() % N;
        int cc = rand() % N;
        if (visible_jugador[rr][cc] != 'X' && visible_jugador[rr][cc] != 'A') {
            *f = rr; *c = cc;
            return;
        }
    }
}

static void convertir_tablero(const char tab[T][T], int b[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(tab[i][j] != '*'){
                b[i][j] = BARCO;
            }
        }
    }
}

static void colocar_flota_manual(int jugador[N][N]){
    char temp[T][T];
    crearTablero(temp);

    printf("\nColoca tus naves\n");
    colocarJugador(temp);
    convertir_tablero(temp,jugador);
}

//Ejecuta una partida completa del juego
void jugarPartida(void){
    srand((unsigned)time(NULL));

    int jugador[N][N], cpu[N][N];
    char tiros_jugador[N][N], tiros_cpu[N][N];

    init_int_board(jugador, AGUA);
    init_int_board(cpu, AGUA);

    // '*' = desconocido
    init_char_board(tiros_jugador, '*');
    init_char_board(tiros_cpu, '*');

    colocar_flota_manual(jugador);//Colocación manual de los barcos
    colocar_flota_aleatoria(cpu);//Colocación aleatoria para el CPU

    int restantes_jugador = total_celdas_barco();
    int restantes_cpu = total_celdas_barco();
    int turnos = 0;

    printf("=== Hundir la flota 12x12 (Humano vs CPU) ===\n");
    printf("Barcos: 1x4, 2x3, 3x2. Total celdas = %d\n", total_celdas_barco());
    printf("Disparo: fila columna (0-11). '*' desconocido, A agua, X acierto.\n");

    while (restantes_jugador > 0 && restantes_cpu > 0) {
        printf("\n-------------------------------------------\n");
        printf("TU TABLERO (B=barco, X=impacto, A=agua):\n");
        imprimir_tablero_propio(jugador);

        printf("\nTUS DISPAROS AL ENEMIGO (* desconocido, X acierto, A agua):\n");
        imprimir_tablero_disparos(tiros_jugador);

        char r = 'X';

        while (r == 'X' && restantes_cpu > 0){ //El jugador puede disparar nuevamente si acierta (X)

        int f, c;
        printf("\nTu disparo (fila col): ");
        if (scanf("%d %d", &f, &c) != 2) {
            printf("Entrada invalida. Saliendo.\n");
            return;
        }
        

        if (!dentro(f, c)) {
            printf("Fuera del tablero. Pierdes el turno (puedes cambiarlo si quieres).\n");
            continue;
        }
        r = disparar(cpu, tiros_jugador, f, c, &restantes_cpu);
        if (r == 0) {
                printf("Ya habias disparado ahi. Intenta de nuevo.\n");
                r = 'X';
                continue;
            }
                turnos++;
                printf("Resultado: %c\n", r); // 'X' o 'A'

                printf("\nTUS DISPAROS AL ENEMIGO (actualizado)\n");
                imprimir_tablero_disparos(tiros_jugador); //Actualiza y muestra el tablero de disparos del jugador
        }

        if (restantes_cpu <= 0) break;

        int cf, cc;
        cpu_elegir_disparo(tiros_cpu, &cf, &cc);
        char rcpu = disparar(jugador, tiros_cpu, cf, cc, &restantes_jugador);

        printf("\nCPU dispara a (%d, %d) -> %c\n", cf, cc, rcpu);
    }

    printf("\n===========================================\n");
    if (restantes_cpu <= 0) {
    printf("GANASTE: hundiste toda la flota enemiga.\n");
    printf("Tu puntuacion: %d turnos\n", turnos);
    guardarPuntuacion(turnos); // Guarda la puntuación solo si el jugador gana
    }else printf("PERDISTE: la CPU hundio toda tu flota.\n");

    printf("\nTUS DISPAROS FINALES:\n");
    imprimir_tablero_disparos(tiros_jugador);

    printf("\nTU TABLERO FINAL:\n");
    imprimir_tablero_propio(jugador);

    return;
}

//Menú principal del juego
int main(void) {
    int op;
    do{
        printf("\n==== MENU ====\n");
        printf("1. Jugar\n");
        printf("2. Ver mejores puntuaciones\n");
        printf("3. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &op) != 1){
            printf("Entrada invalida.\n");
            return 0;
        }
    
        switch(op){
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
    } while(op != 3);

    return 0;
}