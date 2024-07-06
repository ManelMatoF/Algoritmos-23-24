#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
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

int sumaSubMax1(int v[], int n){
    int i,j;
    int estaSuma, sumaMax = 0;
    for(i = 0; i < n; i++){
        estaSuma = 0;
        for(j = i; j < n; j++) {
            estaSuma += v[j];
            if (estaSuma > sumaMax)
                sumaMax = estaSuma;
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[], int n){
    int estaSuma = 0, sumaMax=0;
    for (int j = 0; j < n; j++) {
        estaSuma = estaSuma + v[j];
        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        } else if(estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}

void listar_vector(int v[], int n){
    int i;
    printf("[");
    for(i = 0; i < n; i++)
        printf("%3d", v[i]);
    printf("%3s", "]");
}

void test1(){
    int i, a, b;
    int v1[6][6]= {
            {-9, 2, -5, -4, 6, 6},
            {4, 0, 9, 2, 5, 20},
            {-2, -1, -9, -7, -1, 0},
            {9, -2, 1, -7, -8, 9},
            {15, -2, -5, -4, 16, 20},
            {7, -5, 6, 7, -7, 15}
    };
    printf("test1\n");
    printf("%23s%16s%16s%16s\n", "", "resultado", "sumaSubMax1", "sumaSubMax2");
    for (i = 0; i < 6; i++) {
        listar_vector(v1[i], 5);
        a =sumaSubMax1(v1[i], 5);
        b = sumaSubMax2(v1[i], 5);
        printf("%16d%16d%16d\n",v1[i][5] ,a, b);
    }
    printf("\n");
}

void test2(){
    int i, a, b;
    int v[9];
    printf("\ntest2\n");
    printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i=0; i<10; i++){
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}


double time_sumaSubMax(int value, int v[], int type_suma(int a[], int n)){
    double ta, tb;
    ta = microsegundos();
    type_suma(v, value);
    tb = microsegundos();
    return tb - ta;
}

double leer_tiempo_pequeño(int value, int v[], int k, int type_suma(int a[], int n)){
    double ta, tb;
    int i;
    ta = microsegundos();
    for(i = 0; i < k; i++)
        type_suma(v, value);
    tb = microsegundos();
    return (tb - ta)/k;
}

void create_vector(int value, int **v) {
    *v = (int*)malloc(value * sizeof(int));
    aleatorio(*v, value);
}

double cotas(int n, double exp, double time){
    double result;
    result = time/pow((double)n, exp);
    return result;
}


void print_results(double time, int type, int i){
    double exp;
    if(type == 1){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 1.8; exp <=2.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if (type == 2){
        printf("\t\t%15.3lf\t", time);
        for(exp = 1.8; exp <=2.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 3){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else{
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
}

int main() {
    int *v = NULL;
    int i;
    double time;

    inicializar_semilla();
    test1();
    test2();

    printf("\n\nSumaSubMax 1\n %2s n %19s t(n) %15s t(n)/n^1.8 %13s t(n)/n^2 %13s t(n)/n^2.2", "", "", "", "", "");
    for(i = 500; i <= 32000; i=i*2){
        create_vector(i, &v);
        printf("\n%6d", i);
        time = time_sumaSubMax(i, v, sumaSubMax1);
        if(time < 500.){
            time = leer_tiempo_pequeño(i, v, 1000, sumaSubMax1);
            printf("\t");
            print_results(time, 1, i);
        }else{
            print_results(time, 2, i);
        }
    }

    printf("\n\nSumaSubMax 2\n %2s n %19s t(n) %15s t(n)/n^0.8 %13s t(n)/n^1 %13s t(n)/n^1.2", "", "", "", "", "");
    for(i = 500; i <=256000; i=i*2){
        create_vector(i, &v);
        printf("\n%6d", i);
        time = time_sumaSubMax(i, v, sumaSubMax2);
        if(time < 500.){
            time = leer_tiempo_pequeño(i, v, 1000, sumaSubMax2);
            print_results(time, 3, i);
        }else{
            print_results(time, 4, i);
        }
        free(v);
    }
    return 0;
}

