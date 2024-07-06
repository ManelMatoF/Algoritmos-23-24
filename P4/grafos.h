
#ifndef PRACTICA4_GRAFOS_H
#define PRACTICA4_GRAFOS_H
#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 1000

typedef int **matriz;

matriz crearMatriz(int n);
void iniMatrizRand(matriz m, int n);
void liberarMatriz(matriz m, int n);
void iniMatriz(matriz m, int **v, int n);

#endif //PRACTICA4_GRAFOS_H
