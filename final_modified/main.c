/*
-----------------------------------------------------------------------------
Nom: main.c

Utilitat:   Aquest programa:
            - Crea una matriu a i dos vectors x i b de manera
            dinàmica.
            - Llegeix d'un fitxer (slx.txt, on x = [1, 2, 3, 4]) el
            contingut de la matriu a i el vector b.
            - Crida el programa gauss.c per calcular el valor del
            vector x i el determinant de la matriu.
            - Finalment, imprierix totes les matrius/vectors i el valor
            obtingut del determinant. En cas de ser un sistema indeterminat,
            retorna un missatge d'error.

Autor@:     Núria Torquet Luna, 03/22/20
-------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int matrix_print_off(int nr, int nc, double **a);
int vector_print_off(int nr, double *x);

int main()
{
    double **a, *b, *x, dummie, det;
    float aij, bi, tol;
    int i, j, n, na, nb, k;
    FILE *finput;
    finput = fopen("sl1.txt", "r");
    tol = 1e-12;

    if(finput == NULL){
        printf("Data file not found\n");
        exit(1);
    }

    fscanf(finput, "%d", &n);
    printf("Dimension of the matrix = %d\n\n", n);

    /*
        Aloquem dinàmicamen les matrius i vectors
    */
    a = (double**)calloc(n, sizeof(double*));
    if(a == NULL){
        printf("Matrix couldn't be created\n");
        exit(1);
    }
    for(i = 0; i < n; i++){
        a[i] = (double*)calloc(n, sizeof(double));
        if(a[i] == NULL){
            printf("Matrix couldn't be created\n");
            exit(1);
        }
    }
    b = (double*)calloc(n, sizeof(double));
    x = (double*)calloc(n, sizeof(double));

    /*
        Llegim els elements de A
    */
    fscanf(finput, "%d %d", &na, &nb);
    for(k = 0; k < na; k ++){
        fscanf(finput, "%d %d %lf", &i, &j, &dummie);
        a[i][j] = dummie;
    }

    for(k = 0; k < nb; k++){
        fscanf(finput, "%d %lf", &j, &dummie);
        b[j] = dummie;
    }

    fclose(finput);

    /*
        Tanquem el fitxer input
    */
    printf("\nMatrix read from input file\n");
    printf("\n Matrix A\n\n");
    matrix_print_off(n, n,a);

    printf("\nVector b\n\n");
    vector_print_off(n, b);

    /*
        Cridem funció d'eliminació Gaussiana
    */
    det = gauss(a, b, x, n, tol);
    if(det == 0){
        printf("Matriu no singular");
        exit(1);
    }

    printf("\nSolution x\n\n");
    vector_print_off(n, x);

    printf("\nDeterminant \n\n %9.4f\n", det);

    /*
        Alliberem espai de les matrius
    */
    for(i = 0; i< n; i++){
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);
    return 0;
}


int matrix_print_off(int nr, int nc, double **a){
    int i, j;
    if(nr <= 0) return (-1);
    if(nc <= 0) return (-2);

    for( i = 0; i <nr; i++){
        for(j = 0; j< nc; j++){
            printf("%20.12e ", a[i][j]);

        }
        printf("\n"); /*Insertar nova línia final fila*/
    }
    return 0;
}

int vector_print_off(int nr, double *x){
    int i;
    if(nr <= 0) return(-1);
    for(i = 0; i< nr; i++){
        printf("%20.12e \n", x[i]);

    }
    printf("\n");
    return(0);

}
