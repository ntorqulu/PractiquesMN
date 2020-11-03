#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int matrix_print_off(int nr, int nc, double **a);
int vector_print_off(int nr, double *x);
double gauss(double **a, double *b, double *x, int n, double tol);

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

    return 0;
}

double gauss(double **a, double *b, double *x, int n, double tol){
    int i, j, k, m, rowx;
    double xfac, temp, temp1, amax;
    double det = 1.0;

    /*
        Comencem efectuant la reduccio
    */

    rowx = 0; /*comptador inercanvis files*/
    for(k = 0; k < n-1; ++k){
        amax = (double)fabs(a[k][k]);
        m = k;
        for(i = k+1; i < n; i++){ /*trobar fila amb pivot major*/
            xfac = (double)fabs(a[i][k]);
            if(xfac > amax){
                amax = xfac;
                m = i;
            }
        }
        if(m != k){ /*intercanvi de files*/
            rowx = rowx + 1;
            temp1 = b[k];
            b[k] = b[m];
            b[m] = temp1;
            for(j = k; j < n; j++){
                temp = a[k][j];
                a[k][j] = a[m][j];
                a[m][j] = temp;

            }
        }
        /*if(fabs(a[k][k]) < tol){return 0;}*/

        for (i = k+1; i < n; ++i){
            xfac = a[i][k]/a[k][k];
            for( j = k+1 ; j < n; ++j){
                a[i][j] = a[i][j] - xfac*a[k][j];
            }
            b[i] = b[i] - xfac*b[k];
        }

    }

    /*
        fem la back substitution
    */
    for(j = 0; j < n; j++){
        k = n-j-1;
        x[k]= b[k];
            for(i = k+1; i <n; ++i){
                x[k] = x[k] - a[k][i] * x[i];
            }
        x[k] = x[k] / a[k][k];
    }

    /*
        i calculem determinant
    */
    for(i = 0; i< n; i++){
        det*=a[i][i];
    }
    if(rowx%2 != 0){det*=(-1);}
    return det;

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
