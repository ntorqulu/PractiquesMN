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

float float_seq(float prev);
float deriv_float(float prev, float error);
double double_seq(double prev);
double deriv_double(double prev, double error);


int main(){
    /*Calcular els 50 primers termes de la següent successió*/
    float next_float = 0.01;
    double next_double = 0.01;
    float error_float = 0.01*(1.19*0.0000001);
    double error_double = 0.01*2.22*pow(10.0, -16);
    printf("Comencem calculant els valors de la successio amb precisio float i double\n");
    printf("ITER\tFloat\tError\tDouble\tError\n");
    for(int i = 0; i < 51; i++){
        printf("%d\t%22.15e\t%22.15e\t%22.15e\t%22.15e\n", i, next_float, error_float, next_double, error_double);
        error_float = deriv_float(next_float, error_float);
        error_double = deriv_double(next_double, error_double);
        next_float = float_seq(next_float);
        next_double = double_seq(next_double);
    }
    return 0;
}

float float_seq(float prev){
    return prev + 3.*prev*(1-prev);
}

float deriv_float(float prev, float error){
    return (-6.*prev + 4.)*error;
}

double double_seq(double prev){
    return prev + 3.*prev*(1-prev);
}

double deriv_double(double prev, double error){
    return (-6.*prev + 4.)*error;
}