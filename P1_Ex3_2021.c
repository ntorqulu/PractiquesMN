#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double initial_function(double x0);
double taylor_function(double x0);

int main(){
    double x0 = 1.0;
    double initial_result = 0.0;
    double taylor_result=0.0;
    printf("x0\t Initial f(x)\t Taylor f(x)\n");
    for(int i = 1; i < 10; i++){
        x0 = x0/10.0;
        initial_result = initial_function(x0);
        taylor_result = taylor_function(x0);
        printf("%e\t %e \t %e\n", x0, initial_result, taylor_result);
    }
    return 0;
}

double initial_function(double x0){
    return (x0-sin(x0))/(x0*x0*x0);
}

double taylor_function(double x0){
    return (1.0/6.0)-((x0*x0)/120.0)+((x0*x0*x0*x0)/(5040));
}
