#include <stdio.h>
#include <stdlib.h>

void interpolacio(double* x, double* f, int n, double* c);
double avalua(double a, double* x, double* c, int n);
double func(double x);

int main()
{

    int n, i;
    double *x, *f, *c, point, x1;

    /*Agafem la taula de valors del fixers taulaValors.txt*/
    FILE* fp;
    fp = fopen("taulaValors.txt", "r");
    fscanf(fp, "%d", &n);
    x = (double*) malloc ((n) * sizeof (double));
    f = (double*) malloc ((n) * sizeof (double));
    c= (double*) malloc ((n)* sizeof (double));
    for(i = 0; i< n; i++){
        fscanf(fp, "%lf %lf", &x[i], &f[i]);
    }
    fclose(fp);

    printf("Generem primer el polinomi interpolador, cercant els valors ci amb newton\n");

    interpolacio(x, f, n, c);

    for(i = 0; i< n; i++){
        printf("c%d:\t\t%lf\n", i, c[i]);
    }

    printf("L'avaluem en un punt\n");
    printf("Intrdueix el punt on vols avaluar el polinomi\n");
    scanf("%lf", &point);
    x1= avalua(point, x, c, n);
    printf("Valor del polinomi interpolador:\t%lf\n", x1);

    free(x);
    free(f);
    free(c);

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
