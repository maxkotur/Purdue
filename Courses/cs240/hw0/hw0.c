/* Maxime Kotur, hw0.c, CS 24000, Fall 2018
 * Last updated August 16, 2018
 */

/* Add any includes here */
#include <stdio.h>
#include "hw0.h"

/* Define compute_hailstone here */
int compute_hailstone(int hail, int array_size){
  if (hail <= 0 || array_size <= 0) {
    return HAILSTONE_ERROR;
  }

  g_hailstone_array[0] = hail;
  for (int i = 1; i < array_size; i++) {
    if (hail % 2 == 0 || hail == 2) {
      hail = hail/2;
      g_hailstone_array[i] = hail;
    }
    else if (hail % 2 == 1 || hail == 1) {
      hail = 3*hail + 1;
      g_hailstone_array[i] = hail;
    }
    else{
      g_hailstone_array[i] = 0;
    }
  }
  int sum = 0;
  for (int i = 0; i < array_size; i++) {
    sum += g_hailstone_array[i];
  }
  return sum;
}

/* Define check_hailstone here */
int check_hailstone(int limiter){
  if (limiter < 1 || g_hailstone_array[0] < 1) {
    return HAILSTONE_ERROR;
  }

  int incorrect = 0;
  for (int i = 0; i < ARRAY_SIZE-1; i++) {
    if (limiter-1 == i) {
      return HAILSTONE_CORRECT;
    }
    if (g_hailstone_array[i+1] == 0) {
       incorrect = i+1;
       return incorrect;
     }
    if (g_hailstone_array[i] % 2 == 0) {
       if (g_hailstone_array[i+1] != g_hailstone_array[i]/2) {
          incorrect = i+1;
          return incorrect;
        }
      }
      if (g_hailstone_array[i] % 2 == 1) {
        if (g_hailstone_array[i+1] != (g_hailstone_array[i]*3)+1) {
          incorrect = i+1;
          return incorrect;
          }
        }
      }
      return HAILSTONE_CORRECT;
    }
/* Remember, you don't need a main function!
 * it is provided by hw0_main.c or hw0_test.o
 */
