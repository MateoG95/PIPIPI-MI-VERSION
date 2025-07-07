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
    "../5 zonas/BELISARIO CSV.csv",
    "../5 zonas/CARAPUNGO CSV.csv",
    "../5 zonas/CENTRO CSV.csv",
    "../5 zonas/COTOCOLLAO CSV.csv",
    "../5 zonas/EL-CAMAL CSV.csv"
};

// Prototipo de función local
void imprimirDatosZona(float datos[][4], float temperaturas[], int cantidadEntradas);

int main() {
    float datos[NUM_ZONAS][30][4];
    float temperaturas[NUM_ZONAS][30];
    int cantidadEntradas[NUM_ZONAS] = {0};
    int opcion, zona;
    char buffer[16];

    // Leer todos los datos al inicio
    for (int i = 0; i < NUM_ZONAS; i++) {
        leerDatosCSVConTemperatura(nombresArchivos[i], datos[i], temperaturas[i], &cantidadEntradas[i]);
    }

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1) Cargar datos de una zona\n");
        printf("2) Cargar los datos actuales (Mas recientes) de una zona\n");
        printf("3) Calcular los promedios historicos de una zona\n");
        printf("4) Calcular las predicciones de una zona\n");
        printf("0) Salir\n");
        printf("Seleccione una opcion: ");

        // Validación de opción
        while (1) {
            fgets(buffer, sizeof(buffer), stdin);
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
            int valido = 1;
            for (size_t i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') {
                    valido = 0;
                    break;
                }
            }
            if (valido && strlen(buffer) > 0) {
                opcion = atoi(buffer);
                if (opcion >= 0 && opcion <= 4) break;
            }
            printf("Opcion invalida. Intente de nuevo: ");
        }

        if (opcion == 0) break;

        printf("\nSeleccione la zona:\n");
        for (int i = 0; i < NUM_ZONAS; i++) {
            printf("%d) %s\n", i + 1, nombresZonas[i]);
        }
        printf("Ingrese el numero de la zona: ");

        // Validación de zona
        while (1) {
            fgets(buffer, sizeof(buffer), stdin);
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
            int valido = 1;
            for (size_t i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') {
                    valido = 0;
                    break;
                }
            }
            if (valido && strlen(buffer) > 0) {
                zona = atoi(buffer) - 1;
                if (zona >= 0 && zona < NUM_ZONAS) break;
            }
            printf("Zona invalida. Intente de nuevo: ");
        }

        if (opcion == 1) {
            printf("\n--- Datos de la zona %s ---\n", nombresZonas[zona]);
            imprimirDatosZona(datos[zona], temperaturas[zona], cantidadEntradas[zona]);
            exportarTodosDatosZona(nombresZonas[zona], datos[zona], temperaturas[zona], cantidadEntradas[zona], "reporte.txt");
        }
        else if (opcion == 2) {
            printf("\n--- Datos actuales de la zona %s ---\n", nombresZonas[zona]);
            printf("PM2.5\tNO2\tSO2\tCO2\tTEMP\n");
            printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                datos[zona][cantidadEntradas[zona]-1][0],
                datos[zona][cantidadEntradas[zona]-1][1],
                datos[zona][cantidadEntradas[zona]-1][2],
                datos[zona][cantidadEntradas[zona]-1][3],
                temperaturas[zona][cantidadEntradas[zona]-1]);
            // Exportar solo los datos actuales
            exportarDatosReporteCompletoConTemp(
                nombresZonas[zona],
                datos[zona][cantidadEntradas[zona]-1],
                NULL,
                NULL,
                temperaturas[zona][cantidadEntradas[zona]-1],
                "reporte.txt"
            );
        }
        else if (opcion == 3) {
            float promedios[4] = {0};
            calcularPromediosHistoricos(datos[zona], cantidadEntradas[zona], promedios);
            float promedioTemp = calcularPromedioHistoricoTemperatura(temperaturas[zona], cantidadEntradas[zona]);
            printf("\n--- Promedios históricos de la zona %s ---\n", nombresZonas[zona]);
            printf("PM2.5\tNO2\tSO2\tCO2\tTEMP\n");
            printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                promedios[0], promedios[1], promedios[2], promedios[3], promedioTemp);
            // Exportar solo los promedios
            exportarDatosReporteCompletoConTemp(
                nombresZonas[zona],
                NULL,
                promedios,
                NULL,
                promedioTemp,
                "reporte.txt"
            );
        }
        else if (opcion == 4) {
            float predicciones[4] = {0};
            predecirNivelesFuturosConTemperatura(datos[zona], temperaturas[zona], cantidadEntradas[zona], predicciones);
            float prediccionTemp = predecirTemperaturaFutura(temperaturas[zona], cantidadEntradas[zona]);
            printf("\n--- Predicciones de la zona %s ---\n", nombresZonas[zona]);
            printf("PM2.5\tNO2\tSO2\tCO2\tTEMP\n");
            printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                predicciones[0], predicciones[1], predicciones[2], predicciones[3], prediccionTemp);

            // Imprimir alertas y mitigaciones en la terminal
            imprimirAlertasYMitigacionesConTemp(predicciones, prediccionTemp);

            // Exportar solo las predicciones
            exportarDatosReporteCompletoConTemp(
                nombresZonas[zona],
                NULL,
                NULL,
                predicciones,
                prediccionTemp,
                "reporte.txt"
            );
            // Exportar alertas y mitigaciones con temperatura
            exportarAlertasYMitigacionesConTemp(predicciones, prediccionTemp, "reporte.txt");
        }
    } while (opcion != 0);

    printf("Programa finalizado.\n");
    return 0;
}

// Función para imprimir los datos de una zona
void imprimirDatosZona(float datos[][4], float temperaturas[], int cantidadEntradas) {
    printf("PM2.5\tNO2\tSO2\tCO2\tTEMP\n");
    for (int i = 0; i < cantidadEntradas; i++) {
        printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", datos[i][0], datos[i][1], datos[i][2], datos[i][3], temperaturas[i]);
    }
}