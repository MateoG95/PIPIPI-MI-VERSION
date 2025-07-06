#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

#define NUM_ZONAS 5

const char* nombresZonas[NUM_ZONAS] = {
    "BELISARIO",
    "CARAPUNGO",
    "CENTRO",
    "COTOCOLLAO",
    "EL-CAMAL"
};

const char* nombresArchivos[NUM_ZONAS] = {
    "../5 ZONAS/BELISARIO CSV.csv",
    "../5 ZONAS/CARAPUNGO CSV.csv",
    "../5 ZONAS/CENTRO CSV.csv",
    "../5 ZONAS/COTOCOLLAO CSV.csv",
    "../5 ZONAS/EL-CAMAL CSV.csv"
};

// Prototipos de funciones auxiliares
void leerDatosCSV(const char* nombreArchivo, float datos[][4], int* cantidadEntradas);
void imprimirDatosZona(float datos[][4], int cantidadEntradas);
void predecirNivelesFuturos(float datos[][4], int cantidad, float prediccion[4]);
void imprimirPromediosHistoricosTodasLasZonas(float datos[NUM_ZONAS][30][4], int cantidadEntradas[NUM_ZONAS], const char* nombresZonas[NUM_ZONAS]);

int main() {
    float datos[NUM_ZONAS][30][4]; // Máximo 30 entradas por zona
    int cantidadEntradas[NUM_ZONAS] = {0};
    int opcion, zona;

    // Leer todos los datos al inicio
    for (int i = 0; i < NUM_ZONAS; i++) {
        leerDatosCSV(nombresArchivos[i], datos[i], &cantidadEntradas[i]);
    }

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1) Iniciar los datos de una zona\n");
        printf("2) Calcular los promedios de una zona\n");
        printf("3) Predecir los datos de una zona\n");
        printf("0) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 0) break;

        printf("\nSeleccione la zona:\n");
        for (int i = 0; i < NUM_ZONAS; i++) {
            printf("%d) %s\n", i + 1, nombresZonas[i]);
        }
        printf("Ingrese el numero de la zona: ");
        scanf("%d", &zona);
        zona--; // Ajustar a índice

        if (zona < 0 || zona >= NUM_ZONAS) {
            printf("Zona invalida.\n");
            continue;
        }

        if (opcion == 1) {
            printf("\n--- Datos de la zona %s ---\n", nombresZonas[zona]);
            imprimirDatosZona(datos[zona], cantidadEntradas[zona]);
            // Guardar datos actuales en reporte
            exportarDatosReporte(datos[zona][cantidadEntradas[zona]-1], NULL, "reporte.txt");
        }
        else if (opcion == 2) {
            float promedios[4] = {0};
            calcularPromediosHistoricos(datos[zona], cantidadEntradas[zona], promedios);
            exportarDatosReporte(promedios, NULL, "reporte.txt");
        }
        else if (opcion == 3) {
            float predicciones[4] = {0};
            predecirNivelesFuturos(datos[zona], cantidadEntradas[zona], predicciones);
            emitirAlertas(predicciones);
            generarRecomendaciones(datos[zona][cantidadEntradas[zona]-1], predicciones);
            exportarDatosReporte(NULL, predicciones, "reporte.txt");
        }
        else {
            printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    printf("Programa finalizado.\n");
    return 0;
}

// Función para imprimir los datos de una zona
void imprimirDatosZona(float datos[][4], int cantidadEntradas) {
    printf("PM2.5\tNO2\tSO2\tCO2\n");
    for (int i = 0; i < cantidadEntradas; i++) {
        printf("%.2f\t%.2f\t%.2f\t%.2f\n", datos[i][0], datos[i][1], datos[i][2], datos[i][3]);
    }
}

// Función para imprimir los promedios históricos de todas las zonas
void imprimirPromediosHistoricosTodasLasZonas(float datos[NUM_ZONAS][30][4], int cantidadEntradas[NUM_ZONAS], const char* nombresZonas[NUM_ZONAS]) {
    for (int zona = 0; zona < NUM_ZONAS; zona++) {
        float promedios[4] = {0};
        calcularPromediosHistoricos(datos[zona], cantidadEntradas[zona], promedios);
        printf("\nPromedios históricos de la zona %s:\n", nombresZonas[zona]);
        printf("PM2.5: %.2f\n", promedios[0]);
        printf("NO2:   %.2f\n", promedios[1]);
        printf("SO2:   %.2f\n", promedios[2]);
        printf("CO2:   %.2f\n", promedios[3]);
    }
}