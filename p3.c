#include <stdio.h>
#include <stdlib.h>

void interpolacio(double* x, double* f, int n, double* c);
double avalua(double a, double* x, double* c, int n);
double func(double x);

int main()
{

    int n, i, choose;
    double *x, *f, *c, x1, x2, step_point, total_dist, point;

    printf("Avaluar funció amb una taula de valors(1) o amb un funció(2)\n");
    scanf("%d", &choose);
    if(choose == 1){
        FILE * finput = fopen("taulaValors.txt", "r");
        fscanf(finput, "%d", &n);
        printf("Nombre de punts a evaluar = %d\n\n", n);
        x = (double*) malloc ((n) * sizeof (double));
        f = (double*) malloc ((n) * sizeof (double));
        for(i = 0; i < n ; i++){
            fscanf(finput, "%lf %lf", &x[i], &f[i]);
        }
        fclose(finput);
        printf("Vectors llegits des de l'input file\n");
    }
    else{
        printf("Introdueix nombre de punts a avaluar\n");
        scanf("%d", &n);
        printf("Nombre de punts a evaluar = %d\n\n", n);
        x = (double*) malloc ((n) * sizeof (double));
        f = (double*) malloc ((n) * sizeof (double));
        total_dist = 2.0;
        step_point = total_dist / (double)(n-1);
        x[0] = -1.0;
        f[0] = func(x[0]);
        printf("Imprimim tuples (xi, fi) dels valors de la funció\n");
        printf("0:\t\t%lf\t%lf\n", x[0], f[0]);
        for( i = 1; i < n; i++){
            x[i] = x[i-1] + step_point;
            f[i] = func(x[i]);
            printf("%d:\t\t%lf\t%lf\n", i, x[i], f[i]);
        }

    }
    c= (double*) malloc ((n)* sizeof (double));

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
    int i, j, k = 0;
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
