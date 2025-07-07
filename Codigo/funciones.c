// filepath: c:\Users\arian\OneDrive\Documents\6to semestre\Programación I\PI-MI VERSION\CODIGO\funciones.c

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Nueva función para predicción considerando temperatura
void predecirNivelesFuturosConTemperatura(float datos[][4], float temperaturas[], int cantidad, float prediccion[4]) {
    float sumaPesos = 0;
    float pesos[30];
    for (int i = 0; i < cantidad; i++) {
        pesos[i] = (float)(i + 1) * temperaturas[i]; // Peso: día * temperatura
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

// Exportar los datos a un archivo de reporte (simple)
void exportarDatosReporte(float actuales[4], float prediccion[4], const char* nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "a");
    if (archivo != NULL) {
        if (actuales)
            fprintf(archivo, "Actuales: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", actuales[0], actuales[1], actuales[2], actuales[3]);
        if (prediccion)
            fprintf(archivo, "Prediccion: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", prediccion[0], prediccion[1], prediccion[2], prediccion[3]);
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para exportar datos.\n");
    }
}

// Exportar reporte completo
void exportarDatosReporteCompleto(const char* nombreZona, float actuales[4], float promedios[4], float prediccion[4], const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (!archivo) return;
    fprintf(archivo, "\n--- Reporte de la zona %s ---\n", nombreZona);
    if (actuales)
        fprintf(archivo, "Actuales: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", actuales[0], actuales[1], actuales[2], actuales[3]);
    if (promedios)
        fprintf(archivo, "Promedios: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", promedios[0], promedios[1], promedios[2], promedios[3]);
    if (prediccion)
        fprintf(archivo, "Prediccin: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f\n", prediccion[0], prediccion[1], prediccion[2], prediccion[3]);
    fprintf(archivo, "-------------------------------\n");
    fclose(archivo);
}

// Nueva función para exportar reporte completo con temperatura
void exportarDatosReporteCompletoConTemp(const char* nombreZona, float actuales[4], float promedios[4], float prediccion[4], float tempExtra, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (!archivo) return;
    fprintf(archivo, "\n--- Reporte de la zona %s ---\n", nombreZona);
    if (actuales)
        fprintf(archivo, "Actuales: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f, TEMP=%.2f\n", actuales[0], actuales[1], actuales[2], actuales[3], tempExtra);
    if (promedios)
        fprintf(archivo, "Promedios: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f, TEMP=%.2f\n", promedios[0], promedios[1], promedios[2], promedios[3], tempExtra);
    if (prediccion)
        fprintf(archivo, "Prediccion: PM2.5=%.2f, NO2=%.2f, SO2=%.2f, CO2=%.2f, TEMP=%.2f\n", prediccion[0], prediccion[1], prediccion[2], prediccion[3], tempExtra);
    fprintf(archivo, "-------------------------------\n");
    fclose(archivo);
}

// Leer datos desde un archivo CSV
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

// Leer datos desde un archivo CSV con temperatura
void leerDatosCSVConTemperatura(const char* nombreArchivo, float datos[][4], float temperaturas[], int* cantidadEntradas) {
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
        char fecha[32];
        float temp;
        if (sscanf(linea, "%31[^,],%f,%f,%f,%f,%f", fecha, &datos[fila][0], &datos[fila][1], &datos[fila][2], &datos[fila][3], &temp) == 6) {
            temperaturas[fila] = temp;
            fila++;
        }
    }
    *cantidadEntradas = fila;
    fclose(archivo);
}

// Exportar todos los datos de una zona a un archivo
void exportarTodosDatosZona(const char* nombreZona, float datos[][4], float temperaturas[], int cantidadEntradas, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (!archivo) return;
    fprintf(archivo, "\n--- Todos los datos de la zona %s ---\n", nombreZona);
    fprintf(archivo, "%-7s%-8s%-8s%-8s%-8s\n", "PM2.5", "NO2", "SO2", "CO2", "TEMP");
    for (int i = 0; i < cantidadEntradas; i++) {
        fprintf(archivo, "%-7.2f%-8.2f%-8.2f%-8.2f%-8.2f\n",
            datos[i][0], datos[i][1], datos[i][2], datos[i][3], temperaturas[i]);
    }
    fprintf(archivo, "-------------------------------\n");
    fclose(archivo);
}

void exportarAlertasYMitigaciones(float prediccion[4], const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (!archivo) return;

    fprintf(archivo, "ALERTAS Y MITIGACIONES:\n");

    // PM2.5
    if (prediccion[0] > 35) {
        fprintf(archivo, "ALERTA: PM2.5 (%.2f) MUY ALTO. Mitigacion: Suspender actividades al aire libre, restringir tráfico y emitir alerta sanitaria.\n", prediccion[0]);
    } else if (prediccion[0] > 15) {
        fprintf(archivo, "ALERTA: PM2.5 (%.2f) excede el limite OMS (15). Mitigacion: Reducir trafico vehicular y actividades al aire libre.\n", prediccion[0]);
    } else {
        fprintf(archivo, "PM2.5 dentro de los limites OMS.\n");
    }

    // NO2
    if (prediccion[1] > 50) {
        fprintf(archivo, "ALERTA: NO2 (%.2f) MUY ALTO. Mitigacion: Parar industrias y restringir circulación vehicular.\n", prediccion[1]);
    } else if (prediccion[1] > 25) {
        fprintf(archivo, "ALERTA: NO2 (%.2f) excede el limite OMS (25). Mitigacion: Limitar emisiones industriales y vehiculares.\n", prediccion[1]);
    } else {
        fprintf(archivo, "NO2 dentro de los limites OMS.\n");
    }

    // SO2
    if (prediccion[2] > 80) {
        fprintf(archivo, "ALERTA: SO2 (%.2f) MUY ALTO. Mitigacion: Cierre inmediato de fuentes industriales y alerta a la población.\n", prediccion[2]);
    } else if (prediccion[2] > 40) {
        fprintf(archivo, "ALERTA: SO2 (%.2f) excede el limite OMS (40). Mitigacion: Controlar emisiones de fabricas y quemas.\n", prediccion[2]);
    } else {
        fprintf(archivo, "SO2 dentro de los limites OMS.\n");
    }

    // CO2
    if (prediccion[3] > 10) {
        fprintf(archivo, "ALERTA: CO2 (%.2f) MUY ALTO. Mitigacion: Evacuar áreas cerradas y ventilar urgentemente.\n", prediccion[3]);
    } else if (prediccion[3] > 4) {
        fprintf(archivo, "ALERTA: CO2 (%.2f) excede el limite OMS (4). Mitigacion: Mejorar ventilacion y reducir fuentes de combustion.\n", prediccion[3]);
    } else {
        fprintf(archivo, "CO2 dentro de los limites OMS.\n");
    }

    fprintf(archivo, "-------------------------------\n");
    fclose(archivo);
}

void exportarAlertasYMitigacionesConTemp(float prediccion[4], float prediccionTemp, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (!archivo) return;

    fprintf(archivo, "ALERTAS Y MITIGACIONES:\n");

    // PM2.5
    if (prediccion[0] > 35) {
        fprintf(archivo, "ALERTA: PM2.5 (%.2f) MUY ALTO. Mitigacion: Suspender actividades al aire libre, restringir tráfico y emitir alerta sanitaria.\n", prediccion[0]);
    } else if (prediccion[0] > 15) {
        fprintf(archivo, "ALERTA: PM2.5 (%.2f) excede el limite OMS (15). Mitigacion: Reducir trafico vehicular y actividades al aire libre.\n", prediccion[0]);
    } else {
        fprintf(archivo, "PM2.5 dentro de los limites OMS.\n");
    }

    // NO2
    if (prediccion[1] > 50) {
        fprintf(archivo, "ALERTA: NO2 (%.2f) MUY ALTO. Mitigacion: Parar industrias y restringir circulación vehicular.\n", prediccion[1]);
    } else if (prediccion[1] > 25) {
        fprintf(archivo, "ALERTA: NO2 (%.2f) excede el limite OMS (25). Mitigacion: Limitar emisiones industriales y vehiculares.\n", prediccion[1]);
    } else {
        fprintf(archivo, "NO2 dentro de los limites OMS.\n");
    }

    // SO2
    if (prediccion[2] > 80) {
        fprintf(archivo, "ALERTA: SO2 (%.2f) MUY ALTO. Mitigacion: Cierre inmediato de fuentes industriales y alerta a la población.\n", prediccion[2]);
    } else if (prediccion[2] > 40) {
        fprintf(archivo, "ALERTA: SO2 (%.2f) excede el limite OMS (40). Mitigacion: Controlar emisiones de fabricas y quemas.\n", prediccion[2]);
    } else {
        fprintf(archivo, "SO2 dentro de los limites OMS.\n");
    }

    // CO2
    if (prediccion[3] > 10) {
        fprintf(archivo, "ALERTA: CO2 (%.2f) MUY ALTO. Mitigacion: Evacuar áreas cerradas y ventilar urgentemente.\n", prediccion[3]);
    } else if (prediccion[3] > 4) {
        fprintf(archivo, "ALERTA: CO2 (%.2f) excede el limite OMS (4). Mitigacion: Mejorar ventilacion y reducir fuentes de combustion.\n", prediccion[3]);
    } else {
        fprintf(archivo, "CO2 dentro de los limites OMS.\n");
    }

    // TEMPERATURA
    if (prediccionTemp > 24) {
        fprintf(archivo, "ALERTA: Temperatura (%.2f) MUY ALTA. Mitigaciones:\n", prediccionTemp);
        fprintf(archivo, "  1) Mantenerse hidratado y protegerse del sol.\n");
        fprintf(archivo, "  2) Adaptar las condiciones y horarios de trabajo.\n");
    } else if (prediccionTemp < 18) {
        fprintf(archivo, "ALERTA: Temperatura (%.2f) MUY BAJA. Mitigaciones:\n", prediccionTemp);
        fprintf(archivo, "  1) Vestirse con varias capas de ropa y proteger las extremidades expuestas (manos, pies, cabeza, cuello, cara).\n");
        fprintf(archivo, "  2) Mantenerse hidratado y alimentado.\n");
    } else {
        fprintf(archivo, "Temperatura dentro de los limites recomendados (18-24).\n");
    }

    fprintf(archivo, "-------------------------------\n");
    fclose(archivo);
}

float predecirTemperaturaFutura(float temperaturas[], int cantidad) {
    float suma = 0, sumaPesos = 0;
    for (int i = 0; i < cantidad; i++) {
        float peso = (float)(i + 1);
        suma += temperaturas[i] * peso;
        sumaPesos += peso;
    }
    return (sumaPesos > 0) ? suma / sumaPesos : 0;
}

float calcularPromedioHistoricoTemperatura(float temperaturas[], int cantidad) {
    float suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += temperaturas[i];
    }
    return (cantidad > 0) ? suma / cantidad : 0;
}

void imprimirAlertasYMitigacionesConTemp(float prediccion[4], float prediccionTemp) {
    printf("ALERTAS Y MITIGACIONES:\n");

    // PM2.5
    if (prediccion[0] > 35) {
        printf("ALERTA: PM2.5 (%.2f) MUY ALTO. Mitigacion: Suspender actividades al aire libre, restringir tráfico y emitir alerta sanitaria.\n", prediccion[0]);
    } else if (prediccion[0] > 15) {
        printf("ALERTA: PM2.5 (%.2f) excede el limite OMS (15). Mitigacion: Reducir trafico vehicular y actividades al aire libre.\n", prediccion[0]);
    } else {
        printf("PM2.5 dentro de los limites OMS.\n");
    }

    // NO2
    if (prediccion[1] > 50) {
        printf("ALERTA: NO2 (%.2f) MUY ALTO. Mitigacion: Parar industrias y restringir circulación vehicular.\n", prediccion[1]);
    } else if (prediccion[1] > 25) {
        printf("ALERTA: NO2 (%.2f) excede el limite OMS (25). Mitigacion: Limitar emisiones industriales y vehiculares.\n", prediccion[1]);
    } else {
        printf("NO2 dentro de los limites OMS.\n");
    }

    // SO2
    if (prediccion[2] > 80) {
        printf("ALERTA: SO2 (%.2f) MUY ALTO. Mitigacion: Cierre inmediato de fuentes industriales y alerta a la población.\n", prediccion[2]);
    } else if (prediccion[2] > 40) {
        printf("ALERTA: SO2 (%.2f) excede el limite OMS (40). Mitigacion: Controlar emisiones de fabricas y quemas.\n", prediccion[2]);
    } else {
        printf("SO2 dentro de los limites OMS.\n");
    }

    // CO2
    if (prediccion[3] > 10) {
        printf("ALERTA: CO2 (%.2f) MUY ALTO. Mitigacion: Evacuar áreas cerradas y ventilar urgentemente.\n", prediccion[3]);
    } else if (prediccion[3] > 4) {
        printf("ALERTA: CO2 (%.2f) excede el limite OMS (4). Mitigacion: Mejorar ventilacion y reducir fuentes de combustion.\n", prediccion[3]);
    } else {
        printf("CO2 dentro de los limites OMS.\n");
    }

    // TEMPERATURA
    if (prediccionTemp > 24) {
        printf("ALERTA: Temperatura (%.2f) MUY ALTA. Mitigaciones:\n", prediccionTemp);
        printf("  1) Mantenerse hidratado y protegerse del sol.\n");
        printf("  2) Adaptar las condiciones y horarios de trabajo.\n");
    } else if (prediccionTemp < 18) {
        printf("ALERTA: Temperatura (%.2f) MUY BAJA. Mitigaciones:\n", prediccionTemp);
        printf("  1) Vestirse con varias capas de ropa y proteger las extremidades expuestas (manos, pies, cabeza, cuello, cara).\n");
        printf("  2) Mantenerse hidratado y alimentado.\n");
    } else {
        printf("Temperatura dentro de los limites recomendados (18-24).\n");
    }

    printf("-------------------------------\n");
}