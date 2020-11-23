#include <stdio.h>
#include <stdlib.h>

void interpolacio(double* x, double* f, int n, double* c);
double avalua(double a, double* x, double* c, int n);
double func(double x);

int main()
{

    int n, i, num_of_points;
    double *x, *f, *c, point, x1, interval_distance;

    /*Calculem el polinomi interpolador de grau 10 a l'interval [-1, 1]*/
    /*Per tant, comencem trobant quins són aquests punts*/
    n = 11;
    interval_distance = 2.0;
    x = (double*) malloc ((n) * sizeof (double));
    f = (double*) malloc ((n) * sizeof (double));
    c= (double*) malloc ((n)* sizeof (double));
    for(i = 0; i< n; i++){
        x[i] = -1.0 + ((interval_distance*i)/10.0);
        f[i] = func(x[i]);
        printf("xi: %lf\t", x[i]);
        printf("fi: %lf\n", f[i]);
    }


    printf("Generem primer el polinomi interpolador, cercant els valors ci amb newton\n");

    interpolacio(x, f, n, c);

    for(i = 0; i< n; i++){
        printf("c%d:\t\t%lf\n", i, c[i]);
    }

    printf("L'avaluem en una xarxa de 200 punts, en el mateix interval\n");
    printf("I guardem cada tupla (punt, output polinomi) en un fitxer taulaValors.txt\n");

    num_of_points = 200;
    FILE* fw;
    fw = fopen("taulaValors.txt", "w");

    for(i = 0; i< num_of_points; i++){
        point = (-1.0)+((double)(interval_distance*i)/199.0);
        x1 = avalua(point, x, c, n);
        printf("Valor del polinomi interpolador:\t%lf\t%lf\n", point, x1);
        fprintf(fw, "%lf\t%lf\n", point, x1);

    }

    fclose(fw);

    return 0;

}


void interpolacio(double* x, double* f, int n, double* c){
    int i, j;
    c[0] = f[0];
    for(i = 1; i < n; i++){
        for( j = n-1; j > i-1; j--){
            f[j] = (f[j] - f[j-1])/(x[j] - x[j-i]);
            c[j] = f[j];
        }

    }
}

double avalua(double a, double* x, double* c, int n){
    int i;
    double r = c[n-1];
    for(i = n-2; i > -1; i--){
        r = r*(a-x[i]);
        r = r + c[i];
    }
    return r;
}

double func(double x){
    return (1/(1+25*(x*x)));
}
