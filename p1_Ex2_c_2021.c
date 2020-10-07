/******************************************************************************
Programa que compara errors de propagació entre la mateixa successió escrita de forma diff:
  SUCCESSIO F
    x0 = 0.01
    xn+1 = xn + 3xn(1-xn)
    
 SUCCESSIO G
    x0 = 0.01
    xn+1 = 4*xn - 3*xn²
    
D'aquesta successio farem:
- taula dels valors de n=1 fins a n=50 en format float i double
- aplicar la formula de propagacio de l'error per a cada iteracio
- estimacio de l'error per a x50
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double seq_f(double prev);
double seq_g(double prev);

int main(){
    /*Calcular els 50 primers termes de la següent successió*/
    double next_f = 0.01;
    double next_g = 0.01;
    double error_double_f = 0.01*2.22*pow(19.0, -16);
    double error_double_g = 0.01*2.22*pow(19.0, -16);
    printf("Comencem comparant els valors de les dues successions\n");
    printf("ITER\tg(x)\tError\tf(x)\tError\n");
    for(int i = 0; i < 51; i++){
        printf("%d\t%22.15e\t%22.15e\t%22.15e\t%22.15e\n", i, next_g, error_double_g, next_f, error_double_f);
        error_double_g = seq_g(error_double_g);
        error_double_f = seq_f(error_double_f);
        next_g = seq_g(next_g);
        next_f = seq_f(next_f);
    }
    return 0;
}

double seq_f(double prev){
    return prev + 3.*prev*(1-prev);
}

double seq_g(double prev){
    return 4.*prev - 3.*(pow(prev, 2.));
}
