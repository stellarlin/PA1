/** 
 * variables, initialization and assignment 
 */

#include <stdio.h>
#include <stdlib.h>

/* global variables without explicit initialization are set to zero */
int alpha; 

/* global variable with an explicit initialization */
int beta = 9876;

int main(void) {
  /* uninitialized local variable may contain ANY value - warning */
  int gamma; 
  
  /* initialized local variable */
  int delta = 1234;
  printf("values: %d, %d, %d, %d\n", alpha, beta, gamma, delta);
  
  /* variables are assigned some values, now initialized */
  alpha = 37;
  gamma = 567;
  printf("alpha and gamma after the assignment: %d, %d\n", alpha, gamma);
  return EXIT_SUCCESS;
}
