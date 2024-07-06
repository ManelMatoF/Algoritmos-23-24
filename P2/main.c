
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ord_ins(int v[], int n){
    int i, x, j;

    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = x;
    }
}

void ord_shell (int v[], int n){
    int incremento, i, tmp, j;
    bool seguir;

    incremento = n;
    while(incremento > 1){
        incremento = incremento / 2;
        for (i = incremento -1; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;
            while (j - incremento >= 0 && seguir) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else {
                    seguir = false;
                }
            }
            v[j] = tmp;
        }
    }
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

void listar_vector(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%3d", v[i]);
    printf("\n");
}

int comprobar_ordenado(int v[], int n){
    int i;
    for(i = 0; i < (n - 1); i++){
        if(v[i]>v[i+1])
            return 0;
    }
    return 1;
}

void test(int v[], int n, void ord_funct(int v[], int n), char ord_type[]){
    listar_vector(v, n);
    printf("ordenado? %d\n", comprobar_ordenado(v, n));
    ord_funct(v, n);
    printf("%s", ord_type);
    listar_vector(v, n);
    printf("ordenado? %d\n", comprobar_ordenado(v, n));
}

void print_test1_result(void (*ord_funct), char ord_type[]){
    int v1[17], v2[10];
    aleatorio(v1, 17);
    printf("Inicialización aleatoria\n");
    test(v1, 17, ord_funct, ord_type);
    printf("\n");
    printf("Inicialización descendente\n");
    descendente(v2, 10);
    test(v2, 10, ord_funct, ord_type);
    printf("\n");
    printf("Inicialización ascendente\n");
    ascendente(v2, 10);
    test(v2, 10, ord_funct, ord_type);
    printf("\n");
}

void create_vector(int n, int **v) {
    *v = (int*)malloc(n * sizeof(int));
    aleatorio(*v, n);
}

double leer_tiempo(int n, int v[], int k, void inicializar_type(int v[], int n), void ord_type(int a[], int n)){
    double ta, tb, t, t1, t2;
    int i;
    inicializar_type(v, n);
    ta = microsegundos();
    ord_type(v, n);
    tb = microsegundos();
    t = tb -ta;
    if(t < 500){
        ta = microsegundos();
        for(i = 0;i < k; i++){
            inicializar_type(v, n);
            ord_type(v, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for(i = 0;i < k; i++){
            inicializar_type(v, n);
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1-t2)/k;
        }
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
        for(exp = 1.8; exp <=2.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if (type == 2){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 1.8; exp <=2.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 3){
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 4){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.8; exp <=1.2; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 5){
        printf("\t\t%15.3lf\t", time);
        for(exp = 1.0; exp <=1.4; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 6){
        printf("(*)\t%15.3lf\t", time);
        for(exp = 1.0; exp <=1.4; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else if(type == 7){
        printf("\t\t%15.3lf\t", time);
        for(exp = 0.94; exp <=1.34; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
    else{
        printf("(*)\t%15.3lf\t", time);
        for(exp = 0.94; exp <=1.34; exp=exp+0.2)
            printf("\t%15.5lf\t", cotas(i, exp, time));
        printf("\n");
    }
}

void print_tabla(int *v, int type, void *inicializar_type, void *ord_type){
    double time;
    int i;
    for(i = 500; i <= 32000; i=i*2){
        create_vector(i, &v);
        printf("\n%6d", i);
        time = leer_tiempo(i, v, 1000, inicializar_type, ord_type);
        if(time < 500.){
            print_time_results(time, type + 1, i);
        }else{
            print_time_results(time, type, i);
        }
        free(v);
    }
}

int main(){
    int *v = NULL;


    inicializar_semilla();
    print_test1_result(ord_ins, "Ordenacion por inserción\n");
    print_test1_result(ord_shell, "Ordenacion shell\n");

    printf("\n\nOrdenacion por insercion con inicializacion aleatoria\n %2s n "
           "%19s t(n) %15s t(n)/n^1.8 %13s t(n)/n^2 %13s t(n)/n^2.2", "", "", "", "", "");
    print_tabla(v, 1, aleatorio, ord_ins);

    printf("\n\nOrdenacion por insercion con inicializacion descendente\n %2s "
           "n %19s t(n) %15s t(n)/n^1.8 %13s t(n)/n^2 %13s t(n)/n^2.2", "", "", "", "", "");
    print_tabla(v, 1, descendente, ord_ins);

    printf("\n\nOrdenacion por insercion con inicializacion ascendente\n %2s n"
           " %19s t(n) %15s t(n)/n^0.8 %13s t(n)/n^1 %13s t(n)/n^1.2", "", "", "", "", "");
    print_tabla(v, 3, ascendente, ord_ins);

    printf("\n\nOrdenacion shell con inicializacion aleatoria\n %2s n %19s t(n)"
           " %15s t(n)/n^1.0 %13s t(n)/n^1.2 %11s t(n)/n^1.4", "", "", "", "", "");
    print_tabla(v, 5, aleatorio, ord_shell);

    printf("\n\nOrdenacion shell con inicializacion descendente\n %2s n %19s "
           "t(n) %15s t(n)/n^0.94 %12s t(n)/n^1.14 %10s t(n)/n^1.34", "", "", "", "", "");
    print_tabla(v, 7, descendente, ord_shell);

    printf("\n\nOrdenacion shell con inicializacion ascendente\n %2s n %19s "
           "t(n) %15s t(n)/n^0.94 %12s t(n)/n^1.14 %10s t(n)/n^1.34", "", "", "", "", "");
    print_tabla(v, 7, ascendente, ord_shell);

    printf("\n(*) -> El calculo del tiempo se realiza mediante bucles de 1000 "
           "iteraciones ya que presentan un tiempo inferior al intervalo de confianza (500µs)\n");

    return 0;
}