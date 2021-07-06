#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double gauss(double** a, double* x, double* b, int n, double tol);

int compute_pivot(double** a, double* x, double *b, int n, double tol, int k);

void print_mat(double** a, double* b, int n);

void print_sol(double* x, int n);

int main(void){
	int n, na, nb, k, i, j;
	int nfil, ncol;
	double dummie, det;
	double **mat;
	double *b, *x;


	FILE *fp;
	fp = fopen("sl1.txt", "r");
	fscanf(fp, "%d", &n);

	nfil = n;
	ncol = n;


	mat = (double**)calloc(nfil, sizeof(double*));
	if(mat == NULL){
		printf("No hi ha prou memòria/n");
		exit(1);
	}

	b = (double*)calloc(nfil, sizeof(double));
    x = (double*)calloc(nfil, sizeof(double));

	for(i = 0; i < nfil; i++){
		mat[i] = (double*)calloc(ncol, sizeof(double));
		if(mat[i] == NULL){
			puts("No hi ha prou memòria/n");
			exit(1);
		}
	}

/*Introduim els valors de la matriu amb un fitxer*/

	fscanf(fp, "%d %d", &na, &nb);
	for(k = 0; k < na; k++){
		fscanf(fp, "%d %d %lf", &i, &j, &dummie);
		mat[i][j] = dummie;

	}

	for(k = 0; k < nb; k++){
		fscanf(fp, "%d %lf", &j, &dummie);
		b[j] = dummie;

	}


	fclose(fp);

print_mat(mat, b, n);

/*Ara ja tenim creada la matriu, el que farem simplement és imprimir-la per comprovar que s'ha guardat correctament/n")*/

det = gauss(mat, x, b, n, 0.0000000000000001);

if(det == 0){
    printf("La matriu és singular, sistema lineal indeterminat");
    exit(1);
}

print_mat(mat, b, n);
print_sol(x, n);


/*Un cop hem operat amb la matriu, la alliberem*/
	for(i = 0; i < nfil; i++){
		free(mat[i]);
	}
	free(mat);
	free(b);
	free(x);

	return 0;
}


double gauss(double** a, double* x, double* b, int n, double tol){
	double det = 1.0;
	double pivot, singular;
	for(int k = 0; k < n; k++){
		for(int i = k+1; i < n; i++){
            singular = compute_pivot(a, x, b, n, tol, k);
            if(singular==0){return 0;}
            pivot = a[i][k]/a[k][k];
            a[i][k] = 0.0;
            for(int j = k+1; j < n; j++){
                a[i][j] = a[i][j]- pivot*a[k][j];
            }
            b[i] = b[i] - pivot*b[k];
		}
	}
	for(int i = 0; i < n; i++){
        det *= a[i][i];
	}

	x[n-1] = b[n-1]/a[n-1][n-1];
	for(int i = n-2; i > -1; i --){
        for(int j = i+1; j < n; j++){
            x[i] = b[i] - a[i][j]*x[j];
        }
	}



	return det;
}


int compute_pivot(double** a, double* x, double* b, int n, double tol, int k){
	double* dummy_a;
	double dummy_b;

	double max_elem = 0.0;
	int row_pivot = k;

	for(int i = k; i < n; i++){
		if(abs(a[i][k]) > abs(max_elem)){
			max_elem = a[i][k];
			row_pivot = i;
		}
	}
	if(abs(max_elem) < tol){return 0;}

	if(row_pivot != k){
		dummy_a = a[k];
		a[k] = a[row_pivot];
		a[row_pivot] = dummy_a;
		dummy_b = b[k];
		b[k] = b[row_pivot];
		b[row_pivot] = dummy_b;
		dummy_b = x[k];
	}

	return 1;
}

void print_mat(double** a, double* b, int n){
    for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%lf\t", a[i][j]);
		}
		printf("||\t%lf\t", b[i]);
        printf("\n");
	}
	printf("\n");
}

void print_sol(double* x, int n){
    for(int i = 0; i <n ; i++){
        printf("%lf\t", x[i]);
    }
}
