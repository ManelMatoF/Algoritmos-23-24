
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "monticulos.h"

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void OrdenarPorMonticulos (int v[], int n){
    pmonticulo M = malloc(sizeof(struct monticulo));
    int i;
    crearMonticulo(v, n, M);
    for(i = 0; i<n; i++)
        v[i] = quitarMenor(M);
    free(M);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++) {
        v[i] = (rand() % m) - n;
    }
}

void ascendente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i]=i+1;
}

void descendente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i]=n-i;
}

int comprobar_ordenado(int v[], int n){
    int i;
    for(i = 0; i < (n - 1); i++){
        if(v[i]>v[i+1])
            return 0;
    }
    return 1;
}

void listar_vector(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%3d", v[i]);
    printf("\n");
}

void test_ordM(int n, void inicializar_type(int v[], int n)){
    int *v = (int*)malloc(n * sizeof(int));
    inicializar_type(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", comprobar_ordenado(v, n));
    OrdenarPorMonticulos(v, n);
    listar_vector(v,n);
    printf("ordenado? %d\n", comprobar_ordenado(v, n));
    printf("\n");
    free(v);
}

double leer_tiempo_ordM(int n, int v[], int k, pmonticulo m, void inicializar_type(int v[], int n)){
    double ta, tb, t, t1, t2;
    int i;
    inicializar_type(v, n);
    ta = microsegundos();
    OrdenarPorMonticulos(v, n);
    tb = microsegundos();
    t = tb -ta;
    if(t < 500){
        ta = microsegundos();
        for(i = 0;i < k; i++){
            inicializar_type(v, n);
            OrdenarPorMonticulos(v, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for(i = 0;i < k; i++)
            inicializar_type(v, n);
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1-t2)/k;
    }
    return t;
}

double leer_tiempo_crearM(int n, int v[], int k, pmonticulo m, void inicializar_type(int v[], int n)){
    double ta, tb, t, t1, t2;
    int i;
    inicializar_type(v, n);
    ta = microsegundos();
    crearMonticulo(v, n, m);
    tb = microsegundos();
    t = tb -ta;
    if(t < 500){
        ta = microsegundos();
        for(i = 0;i < k; i++){
            inicializar_type(v, n);
            crearMonticulo(v, n, m);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for(i = 0;i < k; i++)
            inicializar_type(v, n);
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1-t2)/k;
    }
    return t;
}


double cotas(int n, double exp, double time){
    double result;
    result = time/pow((double)n, exp);
    return result;
}

void print_time_results(double time, int type, int i){
    double exp;
    if(type == 1){
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if (type == 2){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 3){
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.90; exp <=1.30; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 4){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.90; exp <=1.30; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 5){
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.87; exp <=1.27; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else{
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.87; exp <=1.27; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
}

void print_tabla(int *v, int type, pmonticulo m, void *inicializar_type, double funct_time (int n, int v[], int k, pmonticulo m, void inicializar_type(int v[], int n))){
    double time;
    int i;
    for(i = 500; i <= 256000; i=i*2){
        v = (int*)malloc(i * sizeof(int));
        printf("\n%6d", i);
        time = funct_time(i, v, 1000, m, inicializar_type);
        if(time < 500.){
            print_time_results(time, type + 1, i);
        }else{
            print_time_results(time, type, i);
        }
        free(v);
    }
}

int main() {
    int *v = NULL;
    pmonticulo m = malloc(sizeof(struct monticulo));

    inicializarMonticulo(m);
    inicializar_semilla();

    test_ordM(15, aleatorio);
    test_ordM(15, ascendente);
    test_ordM(15, descendente);

    printf("\n\nCrearMonticulo en O(n)\n %2s n "
           "%19s t(n) %15s t(n)/n^0.8 %13s t(n)/n^1 %13s t(n)/n^1.2", "", "", "", "", "");
    print_tabla(v, 1, m, aleatorio, leer_tiempo_crearM);

    printf("\n\nOrdenacion por monticulos con inicializacion aleatoria\n %2s n "
           "%19s t(n) %15s t(n)/n^0.90 %13s t(n)/n^1.10 %13s t(n)/n^1.30", "", "", "", "", "");
    print_tabla(v, 3, m, aleatorio, leer_tiempo_ordM);

    printf("\n\nOrdenacion por monticulos con inicializacion ascendente\n %2s n "
           "%19s t(n) %15s t(n)/n^0.87 %13s t(n)/n^1.07 %13s t(n)/n^1.27", "", "", "", "", "");
    print_tabla(v, 5, m, ascendente, leer_tiempo_ordM);

    printf("\n\nOrdenacion por monticulos con inicializacion descendente\n %2s n "
           "%19s t(n) %15s t(n)/n^0.87 %13s t(n)/n^1.07 %13s t(n)/n^1.27", "", "", "", "", "");
    print_tabla(v, 5, m, descendente, leer_tiempo_ordM);

    free(m);
}