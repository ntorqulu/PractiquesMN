/*Matrius quadrades obtingudes de l'input d'un fitxer*/
/*Format del fitxer:*/
/*primera línea --> dimensió matriu, n*/
/*segona línea --> nombre d'elem diff de 0, na; terme independent, nb*/
/*termes de la matriu diff de 0 amb el format i, j, aij*/
/*termes independents diff de 0 format i, bi*/
/*El nostre programa llegeix aquests fitxers i crea matrius de forma dinàmica*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	int n, na, nb, k, i, j;
	int nfil, ncol;
	double dummie;
	double **mat;
	
	FILE *fp;
	fp = fopen("matA.txt", "r");
	fscanf(fp, "%d", &n);
	
	nfil = n;
	ncol = n;
	
	mat = (double**) calloc (nfil + 1, sizeof(double*));
	if(mat == NULL){
		printf("No hi ha prou memòria/n");
		exit(1);
	}
	
	for(i = 0; i < nfil + 1; i++){
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
		mat[3][j] = dummie;
		
	}

	
	fclose(fp);


/*Ara ja tenim creada la matriu, el que farem simplement és imprimir-la per comprovar que s'ha guardat correctament/n")*/
	for(j = 0; j < ncol; j++){
		for(i = 0; i < nfil + 1; i++){
			printf("%lf\t", mat[i][j]);
		}
	printf("\n");
	}

/*Un cop hem operat amb la matriu, la alliberem*/
	for(i = 0; i < nfil+1; i++){
		free(mat[i]);
	}
	free(mat);

	return 0;
}

/*Observacio: Falta la fila de termes independents*/