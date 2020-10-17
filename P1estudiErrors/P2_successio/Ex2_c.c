/******************************************************************************
Programa que calcula els termes de la successio:
    x0 = 0.01
    xn+1 = xn + 3xn(1-xn)
D'aquesta successio farem:
- taula dels valors de n=1 fins a n=50 en format float i double
- aplicar la formula de propagacio de l'error per a cada iteracio
- estimacio de l'error per a x50
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

double seq_f(double prev);
double seq_g(double prev);
double seq_deriv(double prev, double error);

int main(){
    /*Calcular els 50 primers termes de la següent successió*/
    double next_f = 0.01;
    double next_g = 0.01;
    double error_f = 0.01*2.22*pow(10.0, -16);
    double error_g = 0.01*2.22*pow(10.0, -16);
    printf("Comencem calculant els valors de la successio amb precisio float i double\n");
    printf("ITER\tF\tError\tG\tError\n");
    for(int i = 0; i < 51; i++){
        printf("%d\t%22.15e\t%22.15e\t%22.15e\t%22.15e\n", i, next_f, error_f, next_g, error_g);
        error_f = seq_deriv(next_f, error_f);
        error_g = seq_deriv(next_g, error_g);
        next_f = seq_f(next_f);
        next_g = seq_g(next_g);
    }
    return 0;
}

double seq_f(double prev){
    return prev + 3.*prev*(1-prev);
}

double seq_deriv(double prev, double error){
    return (-6.*prev + 4.)*error;
}

double seq_g(double prev){
    return 4*prev -3*(prev*prev);
}
