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
void predecirNivelesFuturosConTemperatura(float datos[][4], float temperaturas[], int cantidad, float prediccion[4]);
void emitirAlertas(float prediccion[4]);
void calcularPromediosHistoricos(float datos[][4], int cantidad, float promedios[4]);
void generarRecomendaciones(float actuales[4], float prediccion[4]);
void exportarDatosReporte(float actuales[4], float prediccion[4], const char* nombreArchivo);
void exportarDatosReporteCompleto(const char* nombreZona, float actuales[4], float promedios[4], float prediccion[4], const char* nombreArchivo);
void exportarDatosReporteCompletoConTemp(const char* nombreZona, float actuales[4], float promedios[4], float prediccion[4], float prediccionTemp, const char* nombreArchivo);
void exportarTodosDatosZona(const char* nombreZona, float datos[][4], float temperaturas[], int cantidadEntradas, const char* nombreArchivo);
void exportarAlertasYMitigaciones(float prediccion[4], const char* nombreArchivo);
void exportarAlertasYMitigacionesConTemp(float prediccion[4], float prediccionTemp, const char* nombreArchivo);
void leerDatosCSVConTemperatura(const char* nombreArchivo, float datos[][4], float temperaturas[], int* cantidadEntradas);
float predecirTemperaturaFutura(float temperaturas[], int cantidad);
float calcularPromedioHistoricoTemperatura(float temperaturas[], int cantidad);
void imprimirAlertasYMitigacionesConTemp(float prediccion[4], float prediccionTemp);

#endif /* FUNCIONES_H */