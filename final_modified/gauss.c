/*
----------------------------------------------------------------------
Nom:        gauss.c
Utilitat:   Calcular sobre una matriu a la reducció per gauss amb
            pivotatge maximal, Ax = b.
            Un cop tenim la matriu triangular, efectuem el back
            substitution per trobar els valors del vector x
            i del determinant de A.
            En cas de ser una matriu indeterminada, retornem 0.
-----------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gauss(double **a, double *b, double *x, int n, double tol);

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
        if(fabs(a[k][k]) < tol){return 0;}

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
