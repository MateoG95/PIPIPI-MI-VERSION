// filepath: c:\Users\arian\OneDrive\Documents\6to semestre\Programación I\PI-MI VERSION\CODIGO\funciones.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Constantes para los límites aceptables
#define LIMITE_PM25 15
#define LIMITE_NO2 25
#define LIMITE_SO2 40
#define LIMITE_CO2 4

// Monitorear la contaminación actual
void monitorearContaminacion(float pm25, float no2, float so2, float co2) {
    if (pm25 > LIMITE_PM25) printf("ALERTA: PM2.5 excede el límite aceptable: %.2f\n", pm25);
    if (no2 > LIMITE_NO2) printf("ALERTA: NO2 excede el límite aceptable: %.2f\n", no2);
    if (so2 > LIMITE_SO2) printf("ALERTA: SO2 excede el límite aceptable: %.2f\n", so2);
    if (co2 > LIMITE_CO2) printf("ALERTA: CO2 excede el límite aceptable: %.2f\n", co2);
}

// Predicción simple de niveles futuros (promedio de los últimos 30 días)
void predecirNivelesFuturos(float datos[][4], int cantidad, float prediccion[4]) {
    // Promedio ponderado: más peso a los días recientes
    float sumaPesos = 0;
    float pesos[30];
    for (int i = 0; i < cantidad; i++) {
        pesos[i] = (float)(i + 1); // Día más reciente tiene mayor peso
        sumaPesos += pesos[i];
    }

    for (int j = 0; j < 4; j++) {
        float suma = 0;
        for (int i = 0; i < cantidad; i++) {
            suma += datos[i][j] * pesos[i];
        }
        prediccion[j] = (sumaPesos > 0) ? suma / sumaPesos : 0;
    }
}

// Emitir alertas si la predicción excede los límites
void emitirAlertas(float prediccion[4]) {
    if (prediccion[0] > LIMITE_PM25) printf("ALERTA: PM2.5 predicho excede el limite: %.2f\n", prediccion[0]);
    if (prediccion[1] > LIMITE_NO2) printf("ALERTA: NO2 predicho excede el limite: %.2f\n", prediccion[1]);
    if (prediccion[2] > LIMITE_SO2) printf("ALERTA: SO2 predicho excede el limite: %.2f\n", prediccion[2]);
    if (prediccion[3] > LIMITE_CO2) printf("ALERTA: CO2 predicho excede el limite: %.2f\n", prediccion[3]);
}

// Calcular el promedio histórico
void calcularPromediosHistoricos(float datos[][4], int cantidad, float promedios[4]) {
    for (int j = 0; j < 4; j++) {
        float suma = 0;
        for (int i = 0; i < cantidad; i++) suma += datos[i][j];
        promedios[j] = (cantidad > 0) ? suma / cantidad : 0;
    }
}

// Generar recomendaciones si los niveles superan los límites
void generarRecomendaciones(float actuales[4], float prediccion[4]) {
    if (actuales[0] > LIMITE_PM25 || prediccion[0] > LIMITE_PM25)
        printf("Mitigacion: Reducir trafico vehicular por PM2.5.\n");
    if (actuales[1] > LIMITE_NO2 || prediccion[1] > LIMITE_NO2)
        printf("Mitigacion: Suspender actividades al aire libre por NO2.\n");
    if (actuales[2] > LIMITE_SO2 || prediccion[2] > LIMITE_SO2)
        printf("Mitigacion: Cierre temporal de industrias por SO2.\n");
    if (actuales[3] > LIMITE_CO2 || prediccion[3] > LIMITE_CO2)
        printf("Mitigacion: Controlar emisiones de CO2.\n");
}

// Exportar los datos a un archivo de reporte
void exportarDatosReporte(float actuales[4], float prediccion[4], const char* nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "a");
    if (archivo != NULL) {
        if (actuales)
            fprintf(archivo, "Actuales: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", actuales[0], actuales[1], actuales[2], actuales[3]);
        if (prediccion)
            fprintf(archivo, "Predicción: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", prediccion[0], prediccion[1], prediccion[2], prediccion[3]);
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para exportar datos.\n");
    }
}

void leerDatosCSV(const char* nombreArchivo, float datos[][4], int* cantidadEntradas) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo: %s\n", nombreArchivo);
        *cantidadEntradas = 0;
        return;
    }
    char linea[256];
    int fila = 0;

    // Saltar la primera línea (encabezado)
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo) && fila < 30) {
        // Saltar la columna de fecha y leer los 4 valores numéricos
        char fecha[32];
        if (sscanf(linea, "%31[^,],%f,%f,%f,%f", fecha, &datos[fila][0], &datos[fila][1], &datos[fila][2], &datos[fila][3]) == 5) {
            fila++;
        }
    }
    *cantidadEntradas = fila;
    fclose(archivo);
}