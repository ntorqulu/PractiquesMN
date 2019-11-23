/*
 * Trobar mitjancant el mètode de les equacions lineals el polinomi interpolador
 * de Lagrange. La classe consta de 3 funcions:
 * - lu --> descomposició de la matriu formada per la substitució dels valors
 *          xi en el polinomi tq està formada per les files <1, xi, xi^2, ..., xn^n>
 * - luSolve --> resol el sistema reutilitzant la descomposició lu. Així aconseguim
 *              trobar els coeficients del polinomi
 * - horner --> permet trobar el valor del polinomi al evaluar-lo en z.
 */

/* 
 * File:   main.c
 * Author: Nuria Torquet Luna
 *
 * Created on November 20, 2019, 6:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 21


int lu(double **a, int n, int *perm, double tol);
void luSolve(double **a, int *perm, double *b, double *c, int n, double *x, double *y);
double horner(int n, double *a, double z);


/**
 * Main del programa, instanciem totes les variables que usarem.
 * @return 
 */
int main(void) {
    
    int n, i, j,k;
    double **M, *y, *b, *c, v;
    double x[N-1], f[N-1], z[N-1];
    int *perm, numOfPerm;
    
    printf("Introdueix el grau del polinomi: ");
    scanf("%d", &n);
    
    
    /*INICIALITZEM LES MATRIUS QUE USAREM*/
    M = (double**) malloc((n+1) * sizeof (double*));
    y = (double*) malloc((n+1) * sizeof (double));
    b = (double*) malloc((n+1) * sizeof (double));
    c = (double*) malloc((n+1) * sizeof (double));
    perm = (int*) malloc((n+1) * sizeof (int));
    
    if(M == NULL || b == NULL || y == NULL || perm == NULL){
        printf("No hi ha prou memòria\n");
        exit(1);
    }
    
    for (i = 0; i <= n; i++) {
        M[i] = (double*) malloc((n+1) * sizeof (double));
        if (M[i] == NULL) {
            printf("No hi ha prou memòria\n");
            exit(2);
        }
    }
    
    printf("Introdueix les coordenades xi i fi dels n+1 punts\n");
	for(i = 0; i <= n; i++){
		scanf("%le %le", &x[i], &b[i]);
                z[i] = x[i];
                perm[i] = i;
	}
    
    printf("\nMatriu del sistema:\n"); 
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= n; j++) {
                M[i][j] = pow(x[i], j);
            }
        }
    
    for(i = 0; i<=n ; i++){
        for(j = 0; j<=n; j++){
            printf("%lf\n", M[i][j]);
        }
    }
    
    printf("Comprovem primer que la matriu no és degenerada\n");
    numOfPerm = lu(M, n+1, perm, 0.000005);
    
    if (numOfPerm == -1) {
        printf("La matriu és degenerada\n");
        exit(3);
    }

    /*Comencem a trobar solució*/
    printf("Calculem coeficients\n");
    
    luSolve(M, perm, b, c, n+1, x, y);
        printf("\nX\n");
        for (j = 0; j <= n; j++) {
            printf("%lf  ", x[j]);/*obtenim llavors els coeficients del polinomi*/
       
    }
    printf("\n");

    printf("Ara avaluarem el polinomi mitjançant el mètode de Horner en el punt z\n");
    printf("Introdueix valor xi que vols interpolar\n");
    scanf("%lf", &v);
    v = horner(n+1, x, v);
    printf("%lf\n", v);
    
    printf("Per comprovar que el polinomi calculat és correcte, podem comprovar que"
            "les imatges dels valors xi == fi al aplicar horner\n");
    int trueHorner = 1;
    for(i = 0; i <= n && trueHorner == 1; i++){
        v = horner(n+1, x, z[i]);
        printf("per horner -->%lf\nresultat esperat--->%lf\n", v, b[i]);
    }
    
    for (i = 0; i <= n; i++) {
        free(M[i]);
    }
    free(M);
    free(b);
    free(c);
    
    free(y);
    free(perm);
    
    
    return (0);
}

/**
 * Mètode per calcular la factorització PA = LU. Per estalviar memòria, la factorització LU
 * es guardarà en la mateixa matriu "a" i P en un vector de permutacions de les files de Id
 * @param a, matriu inicial que volem descomposar
 * @param n, mida de la matriu a
 * @param perm, vector que guardarà les permutacions de Id
 * @param tol, tolerància amb la que considerarem si la matriu A és non-singular
 * @return numOfPerm, el nombre de permutacions que hem fet a Id si A és non-singular
 *                    -1 en el cas que A no es pugui factoritzar(l.dependent, det(A) = 0)
 */
int lu(double **M, int n, int *perm, double tol) {
    
    int i, j, indxMax, k, numOfPerm;
    double max, *ptr;
    numOfPerm = 0;

    for (i = 0; i < n; i++) {
        
        max = 0.0;
        indxMax = i;

        for (k = i; k < n; k++) {
            if (fabs(M[k][i]) > max) {
                max = fabs(M[k][i]);
                indxMax = k;

            }
        }
        if (max < tol) return -1; 

        if (indxMax != i) {
           
            numOfPerm += 1;
            j = perm[i]; 
            perm[i] = perm[indxMax];
            perm[indxMax] = j;

            
            ptr = M[i];
            M[i] = M[indxMax];
            M[indxMax] = ptr;
        }
        for (j = i + 1; j < n; j++) {
            M[j][i] = M[j][i] / M[i][i];

            for (k = i + 1; k < n; k++) {
                M[j][k] = M[j][k]- (M[j][i] * M[i][k]);
            }
        }
    }

    return numOfPerm;
}


/**
 * 
 * @param a
 * @param perm
 * @param b
 * @param c
 * @param n
 * @param x
 * @param y
 */

void luSolve(double **a, int *perm, double *b, double *c, int n, double *x, double *y) {

    /* Sabem que Ax=b i PA = LU p.t. PLUx = b
    Comencem substituint Ux = y i calculem PLy = b --> Ly = Pb */

    double sum = 0.0;
    int i = 0, k = 0;

    for (i = 0; i < n; i++) {
        c[i] = b[perm[i]]; 
        x[i] = 0.0;
    }

    /*Fem ús del codi de la classe ResolucioMatriuTriang per resoldre matrius 
     * triangulars inf amb 1's diagonal.
     */
    for (i = 0; i <= n - 1; i++) {
        sum = 0.0;
        for (k = 0; k < i; k++) {
            sum += a[i][k] * y[k];

        }
        y[i] = (c[i] - sum);
    }

    /*Fem ús del codi resolució matrius triangulars superiors
     */
    for (i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (k = i + 1; k < n; k++) {
            sum += a[i][k] * x[k];
        }
        x[i] = (y[i] - sum) / a[i][i];
    }

}
double horner(int n, double *a, double z){
    double v = a[n];
    int i;
    for(i = n-1; i>=0; i--){
        v = v*z+a[i];
    }
    return v;
}



