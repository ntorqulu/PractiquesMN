/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: anakinskywalker
 *
 * Created on November 23, 2019, 5:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define N 21

void dif_div(int n, double *x, double *f);
double hornerNew(int n, double *b, double *x, double z);
/*
 * 
 */
int main(void) {
    int n, i;
    double x[N-1], f[N-1], v, z;
    
    printf("Introdueix el grau del polinomi: ");
    scanf("%d", &n);
    
    printf("Introdueix el valor dels punts (xi, fi) en forma de tuples");
    for(i = 0; i<= n; i++){
        scanf("%le %le", &x[i], &f[i]);  
    }
    
    /*ara cridem la funcio dif_div, que donats els vectors x i f ens retornarà
     el vector f modificat amb les diferències dividides*/
    dif_div(n, x, f);
    for(i = 0; i<= n; i++){
        printf("%le\n", f[i]);
    }
    
    
   printf("Introdueix valor que vols interpolar\n");
   scanf("%lf", &z);
   
   v = hornerNew(n, x, f, z);
   printf("Resultat d'avaluar la funció amb el mètode de Horner\n");
   printf("%lf\n", v);
    
    return (0);
}

void dif_div(int n, double *x, double *f){
    int i, j;
    for(i = 1; i<=n; i++){
        for(j = n; j>=i; j--){
            f[j] = (f[j]-f[j-1])/(x[j]-x[j-i]);
        }
    }
}
/*
 evalua polinomi interpolador a z*/
double hornerNew(int n, double *x, double *f, double z){
    double v = f[n];
    int i;
    for(i = n-1; i>=0; i--){
        v = v*(z-x[i])+f[i];
    }
    return v;
}