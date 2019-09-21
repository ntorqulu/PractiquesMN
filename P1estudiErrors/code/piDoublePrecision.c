#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI acos(-1.0)

/**

*/

double piArquimedes(int n);
double recurrenciaCircumscrit(double longArestaInsQuad);

int main(void){
        int iterations;
	int vertex =2;
        double resultatIns, resultatCircums, longArestaInsQuad, longArestaIns, longArestaCircums,
		errorIns, errorCircums;

        for(iterations = 0; iterations <16; iterations++){
                longArestaInsQuad = piArquimedes(iterations);
		longArestaCircums = recurrenciaCircumscrit(longArestaInsQuad);
		longArestaIns = sqrt(longArestaInsQuad);
                vertex *= 2;
		resultatIns =(vertex*longArestaIns)/2;
		resultatCircums = (vertex*longArestaCircums)/2;
		errorIns = fabs(M_PI- resultatIns)/M_PI;
		errorCircums = fabs(M_PI- resultatCircums)/M_PI;
                printf("%d     %lf     %lf", vertex, resultatIns, errorIns);
                printf("\n");
		printf("%d     %lf     %lf", vertex, resultatCircums, errorCircums);
                printf("\n");
        }

	
        return(0);
}

double recurrenciaCircumscrit(double longArestaInsQuad){
	double longArestaIns = sqrt(longArestaInsQuad);
	return ( 2.0*longArestaIns)/sqrt(4.0-longArestaInsQuad);
}

double piArquimedes(int n){
        int i;
        double longArestaInsQuad = 2.0;
        for(i = 0; i < n; i++){
                longArestaInsQuad = 2.0-sqrt(4.0-longArestaInsQuad);                
        	}
        return longArestaInsQuad;
}
