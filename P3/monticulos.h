
#ifndef P3_MAIN_H
#define P3_MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

bool monticuloVacio(pmonticulo m);
void crearMonticulo(int v [], int n, pmonticulo m);
int quitarMenor(pmonticulo m);
void inicializarMonticulo(pmonticulo m);


#endif