#include <stdio.h>
#include <math.h>

#define N 256

void menu();
void cargarAudio(char *nombreArchivo, int porcion);
void calcularFFT(int *porcionAudio, float *potenciaFrecuencia);
void representacionGrafica(float *potenciaFrecuencia);
void cargarArchivoAudio(char *nombreArchivo, float *porcionAudio, int tamanioPorcion);


int main() {
    menu();
    return 0;
}

void menu() {
    int opcion, porcion;
    float porcionAudio[1000];
    char nombreArchivo[1000];

    printf("\nMenu\n");
    printf("1. Cargar porcion de audio\n");
    printf("2. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
        printf("Ingrese el nombre del archivo de audio: ");
            scanf("%s", nombreArchivo);
            printf("Ingrese la porcion de audio a cargar (en segundos): ");
            scanf("%d", &porcion);
            cargarArchivoAudio(nombreArchivo, porcionAudio, 1000);
            cargarAudio(nombreArchivo, porcion);
            break;
        case 2:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida. Intente de nuevo.\n");
            menu();
            break;
    }
}

void cargarAudio(char *nombreArchivo, int porcion) {
    FILE *archivo;
    int porcionAudio[N];
    float potenciaFrecuencia[N];
    int i;

    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de audio.\n");
        return;
    }

    // Leer la información necesaria del encabezado del archivo WAV
    // ...

    // Leer porciones (bytes) de audio y guardarlos en un arreglo en RAM
    for (i = 0; i < N; i++) {
        fread(&porcionAudio[i], sizeof(int), 1, archivo);
    }

    calcularFFT(porcionAudio, potenciaFrecuencia);
    representacionGrafica(potenciaFrecuencia);

    fclose(archivo);
}

void cargarArchivoAudio(char *nombreArchivo, float *porcionAudio, int tamanioPorcion) {
    FILE *archivoAudio = fopen(nombreArchivo, "rb");
    if (archivoAudio == NULL) {
        printf("Error al abrir el archivo de audio");
        return;
    }

    fread(porcionAudio, sizeof(float), tamanioPorcion, archivoAudio);
    fclose(archivoAudio);
}

void calcularFFT(int *porcionAudio, float *potenciaFrecuencia) {
    int i;
    float real, imag;

    // Aplicar la Transformada Rápida de Fourier (FFT) a la porción de audio
    for (i = 0; i < N; i++) {
        // Cálculo de la FFT

        // Cálculo de la potencia de frecuencia
        potenciaFrecuencia[i] = sqrt(pow(real, 2) + pow(imag, 2));
    }
}

void representacionGrafica(float *potenciaFrecuencia) {
    int i, j;
    int nivelesPotencia;

    for (i = 0; i < N; i++) {
        nivelesPotencia = potenciaFrecuencia[i] * 10;
        for (j = 0; j < nivelesPotencia; j++) {
            printf("*");
        }
        printf("\n");
    }
}
