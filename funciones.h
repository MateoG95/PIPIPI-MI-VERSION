#ifndef FUNCIONES_H
#define FUNCIONES_H

// Constantes para los límites aceptables de contaminación
#define LIMITE_PM25 15
#define LIMITE_NO2 25
#define LIMITE_SO2 40
#define LIMITE_CO2 4

// Prototipos de funciones
void leerDatosCSV(const char* nombreArchivo, float datos[][4], int* cantidadEntradas);
void monitorearContaminacion(float pm25, float no2, float so2, float co2);
void predecirNivelesFuturos(float datos[][4], int cantidad, float prediccion[4]);
void emitirAlertas(float prediccion[4]);
void calcularPromediosHistoricos(float datos[][4], int cantidad, float promedios[4]);
void generarRecomendaciones(float actuales[4], float prediccion[4]);
void exportarDatosReporte(float actuales[4], float prediccion[4], const char* nombreArchivo);

#endif /* FUNCIONES_H */