//Autores: Raul Mateo Sanguino, Agoney Hernández Trujillo, Marc Anjelo Canlas Castañeda
//Proposito: Crear ranking de puntuaciones

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PUNTUACIONES 3
#define FICHERO_PUNTUACIONES "puntuaciones.dat"

/* Estructura de una puntuación */
typedef struct {
    int turnos;              /* puntuación */
    char fecha[11];          /* YYYY-MM-DD */
    char hora[9];            /* HH:MM:SS */
} Puntuacion;

/* Prototipos internos */
void obtenerFechaHoraActual(char fecha[], char hora[]);

/* Guarda una nueva puntuación */
void guardarPuntuacion(int turnos) {
    Puntuacion p[MAX_PUNTUACIONES + 1];
    int total = 0;
    FILE *f;

    /* Leer puntuaciones existentes */
    f = fopen(FICHERO_PUNTUACIONES, "rb");
    if (f != NULL) {
        while (total < MAX_PUNTUACIONES &&
               fread(&p[total], sizeof(Puntuacion), 1, f) == 1) {
            total++;
        }
        fclose(f);
    }

    /* Añadir nueva puntuación */
    p[total].turnos = turnos;
    obtenerFechaHoraActual(p[total].fecha, p[total].hora);
    total++;

    /* Ordenar por número de turnos (menor es mejor) */
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (p[j].turnos > p[j + 1].turnos) {
                Puntuacion aux = p[j];
                p[j] = p[j + 1];
                p[j + 1] = aux;
            }
        }
    }

    /* Guardar solo las mejores puntuaciones */
    if (total > MAX_PUNTUACIONES) {
        total = MAX_PUNTUACIONES;
    }

    f = fopen(FICHERO_PUNTUACIONES, "wb");
    if (f == NULL) {
        printf("Error al abrir el fichero de puntuaciones.\n");
        return;
    }

    fwrite(p, sizeof(Puntuacion), total, f);
    fclose(f);
}

/* Muestra las mejores puntuaciones */
void mostrarMejoresPuntuaciones(void) {
    FILE *f;
    Puntuacion p;
    int posicion = 1;

    f = fopen(FICHERO_PUNTUACIONES, "rb");
    if (f == NULL) {
        printf("\nNo hay puntuaciones guardadas.\n\n");
        return;
    }

    printf("\n--- MEJORES PUNTUACIONES ---\n");
    while (fread(&p, sizeof(Puntuacion), 1, f) == 1) {
        printf("%d) %d turnos - %s %s\n",
               posicion, p.turnos, p.fecha, p.hora);
        posicion++;
    }
    printf("\n");

    fclose(f);
}

/* Obtiene fecha y hora actual */
void obtenerFechaHoraActual(char fecha[], char hora[]) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    sprintf(fecha, "%04d-%02d-%02d",
            tm_info->tm_year + 1900,
            tm_info->tm_mon + 1,
            tm_info->tm_mday);

    sprintf(hora, "%02d:%02d:%02d",
            tm_info->tm_hour,
            tm_info->tm_min,
            tm_info->tm_sec);
}