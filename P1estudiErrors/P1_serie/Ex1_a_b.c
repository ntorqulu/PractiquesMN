/******************************************************************************
Fer un programa que calculi la suma de la serie 1/i terme a terme per j = 1...n
i per k = n...1, es a dir, en ordre creixent i decreixent.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

//funciio per a calcular la serie harmonica tant del dret com del reves
float sum_serie (float prev_value, int iter);


int main ()
{
  /*Comencem calculant (a), la serie harmonica en ordre creixent */
  printf ("Calcul de la serie en ordre creixent\n");

  int iter = 1;			//comptador del nombre d'iteracions, index i en la formula
  float prev = 0.0;		//valor sn-1 de la serie
  float next = 1.0;		//valor sn de la serie

  float sum_creixent = 0.0;

  printf ("Iteracio numero\tSn val\n");
  while ((next - prev)!=0)
    {
      iter += 1;
      prev = next;
      next = sum_serie (next, iter);
      printf ("%d\t%22.15e\n", iter - 1, prev);
    }
  printf ("%d\t%22.15e\n", iter, next);
  printf ("Numero d'iteracions fetes en ordre creixent: %d\n", iter);
  sum_creixent = next;
  printf ("Sumatori de la serie en ordre creixent val: %22.15e\n", next);
  printf("\n");

  /*
     Un cop calculat l'ordre creixent, calculem (b), comencant pel valor de n == iter anterior
   */
  printf ("Calcul de la serie en ordre decreixent\n");
  prev = 0.0;
  next = 0.0;
  while (iter != 0)
    {
      prev = next;
      next = sum_serie (next, iter);
      printf ("%d\t%22.15e\n", iter, next);
      iter -= 1;
    }
  printf ("Sumatori de la serie en ordre creixent val: %22.15e\n", sum_creixent);
  printf ("Sumatori de la serie en ordre decreixent val: %22.15e\n", next);

  return 0;
}

float
sum_serie (float prev_value, int iter)
{

  float var = prev_value + (1.0 / iter);
  return var;

}