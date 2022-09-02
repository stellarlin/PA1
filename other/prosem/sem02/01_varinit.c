/** 
 * variables and initialization 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int alpha = 0;
  printf("initialized: %d\n", alpha);
  alpha = 37;
  printf("assignment: %d\n", alpha);
  printf("expression alpha+4: %d\n", alpha+4);
  return EXIT_SUCCESS;
}
