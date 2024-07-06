
#include "monticulos.h"

bool monticuloVacio(pmonticulo m){
    return m->ultimo == -1;
}

void inicializarMonticulo(pmonticulo m){
    m->ultimo=-1;
}

void Hundir(pmonticulo m, int i) {
    int HijoIzq, HijoDer, j, temp;
    do {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2 ;
        j = i;

        if (HijoDer <= m->ultimo && m->vector[HijoDer] < m->vector[i])
            i = HijoDer;

        if (HijoIzq <= m->ultimo && m->vector[HijoIzq] < m->vector[i])
            i = HijoIzq;

        if (j != i) {
            temp = m->vector[i];
            m->vector[i] = m->vector[j];
            m->vector[j] = temp;
        }

    } while (j != i);
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    int i;
    m->ultimo = n - 1;
    memcpy(m->vector, v, n * sizeof(int));
    for (i = m->ultimo / 2; i >= 0; i--) {
        Hundir(m, i);
    }
}

int quitarMenor(pmonticulo m){
    if(monticuloVacio(m)){
        fprintf(stderr, "Error: Montículo vacío\n");
        return -1;
    }
    else{
        int x;
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo --;
        Hundir(m, 0);
        return x;
    }
}
