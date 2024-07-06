
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include"grafos.h"

void dijkstra(matriz grafo, matriz distancias, int tam) {
    int n, i, j, v = 0;
    int* noVisitados = malloc(tam * sizeof(int));

    for (n = 0; n < tam; n++) {
        for (i = 0; i < tam; i++) {
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;

        for (int count = 0; count < tam - 2; count++) {
            v = -1;

            for (i = 0; i < tam; i++) {
                if(noVisitados[i] && (v == -1 || distancias[n][i] < distancias[n][v])){
                    v = i;
                }
            }

            noVisitados[v] = 0;

            for (j = 0; j < tam; j++) {
                if(noVisitados[j] && distancias[n][j] > distancias[n][v] + grafo[v][j]){
                    distancias[n][j] = distancias[n][v] + grafo[v][j];
                }
            }
        }
    }

    free(noVisitados);
}

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
void print_matriz(matriz m, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++)
            printf("%d%s", m[i][j], "  ");
        printf("\n");
    }
}

void test_dijkstra(int tam, int **v, matriz grafo, matriz distancias){
    grafo = crearMatriz(tam);
    distancias = crearMatriz(tam);

    iniMatriz(grafo, v, tam);
    dijkstra(grafo, distancias, tam);
    printf("Matriz de adyacencia\n");
    print_matriz(grafo, tam);
    printf("\n");
    printf("Distancias minimas\n");
    print_matriz(distancias, tam);
    printf("\n\n");

    liberarMatriz(grafo, tam);
    liberarMatriz(distancias, tam);
}

int **crear_vector(int rows, int cols, int values[rows][cols]){

    int **v, i, j;
    v = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        v[i] = (int *)malloc(cols * sizeof(int));
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            v[i][j] = values[i][j];
        }
    }
    return v;
}

void free_vector(int **v, int tam){
    int i;
    for (i = 0; i < tam; i++)
        free(v[i]);
    free(v);
}

double leer_tiempo(int n, int k, matriz grafo, matriz distancias){
    double ta, tb, t, t1, t2;
    int i;
    iniMatrizRand(grafo, n);
    ta = microsegundos();
    dijkstra(grafo, distancias, n);
    tb = microsegundos();
    t = tb -ta;
    if(t < 500){
        ta = microsegundos();
        for(i = 0;i < k; i++){
            iniMatrizRand(grafo, n);
            dijkstra(grafo, distancias, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for(i = 0;i < k; i++)
            iniMatrizRand(grafo, n);
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
        for(exp = 2.6; exp <3.1; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else{
        printf("(*)\t%15.3lf\t", time);
        for(exp = 2.6; exp <3.1; exp=exp+0.2)
            printf("\t%15.6lf\t", cotas(i, exp, time));
        printf("\n");
    }
}

void print_tabla(int type, matriz grafo, matriz distancias){
    double time;
    int i;

    for(i = 15; i <= 960; i=i*2){
        grafo = crearMatriz(i);
        distancias = crearMatriz(i);

        printf("\n%6d", i);
        time = leer_tiempo(i, 1000, grafo, distancias);
        if(time < 500.){
            print_time_results(time, type + 1, i);
        }else{
            print_time_results(time, type, i);
        }

        liberarMatriz(grafo, i);
        liberarMatriz(distancias, i);
    }
}

int main(){
    int **v;
    matriz grafo, distancias;

    int values[5][4] = {{1, 8, 4, 7}, {1, 2, 6, 5}, {8, 2, 9, 5}, {4, 6, 9, 3},
                        {7, 5, 5, 3}};
    int values2[4][3] = {{1, 4, 7}, {1, 2, 8}, {4, 2, 3}, {7, 8, 3}};

    grafo = distancias = NULL;

    v = crear_vector(5, 4, values);
    test_dijkstra( 5, v, grafo, distancias);
    free_vector(v, 5);

    v = crear_vector(4, 3, values2);
    test_dijkstra(4, v, grafo, distancias);
    free_vector(v, 4);

    printf("\n\nComprobacion empirica de la complejidad de dijkstra\n %2s n "
           "%19s t(n) %15s t(n)/n^2.6 %12s t(n)/n^2.8 %12s t(n)/n^3.0", "", "", "", "", "");
    print_tabla(1, grafo, distancias);

    printf("\n(*) -> El calculo del tiempo promedio se realiza mediante bucles de 1000 "
           "iteraciones ya que presentan un tiempo inferior al intervalo de confianza (500µs)\n");
}