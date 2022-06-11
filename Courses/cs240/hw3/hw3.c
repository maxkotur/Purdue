/*
 * Maxime Kotur, hw3.c, CS 24000, Fall 2018
 * Last updated September 13, 2018
 */

#include "hw3.h"

#include <math.h>

/*
 * complex_add function
 */

complex complex_add(complex num1, complex num2) {
  complex add;
  add.x = num1.x+num2.x;
  add.y = num1.y+num2.y;
  return add;
} /* complex_add() */

/*
 * complex_neg function
 */

complex complex_neg(complex num1) {
  complex neg;
  neg.x = -1.0*num1.x;
  neg.y = -1.0*num1.y;
  return neg;
} /* complex_neg() */

/*
 * complex_sub function
 */

complex complex_sub(complex num1, complex num2) {
  complex sub;
  sub.x = num1.x-num2.x;
  sub.y = num1.y-num2.y;
  return sub;
} /* complex_sub() */

/*
 * complex_dot function
 */

double complex_dot(complex num1, complex num2) {
  return (num1.x*num2.x)+(num1.y*num2.y);
} /* complex_dot() */

/*
 * complex_inv function
 */

complex complex_inv(complex num1) {
  double sum = num1.x*num1.x+num1.y*num1.y;
  complex inv;
  inv.x = num1.x/sum;
  inv.y= -num1.y/sum;
  return inv;
} /* complex_inv() */

/*
 * complex_mul function
 */

complex complex_mul(complex num1, complex num2) {
  complex mul;
  mul.x = num1.x*num2.x-num1.y*num2.y;
  mul.y = num1.x*num2.y+num1.y*num2.x;
  return mul;
} /* complex_mul() */

/*
 * complex_div function
 */

complex complex_div(complex num1, complex num2) {
  complex divi = complex_mul(num1, complex_inv(num2));
  return divi;
} /* complex_div() */

/*
 * complex_exp function
 */

complex complex_exp(complex num1) {
  complex expo;
  expo.x = exp(num1.x)*cos(num1.y);
  expo.y = exp(num1.x)*sin(num1.y);
  return expo;
} /* complex_exp() */

/*
 * mandelbrot function
 */

int mandelbrot(complex num1) {
  complex mandel;
  mandel.x = 0;
  mandel.y = 0;
  int num_calculations = 0;
  while (num_calculations != MAX_MANDELBROT) {
    if (complex_dot(mandel, mandel) > 4.0) {
      break;
    }
    mandel = complex_mul(mandel, mandel);
    mandel = complex_add(mandel, num1);
    num_calculations++;
  } /* loop to find end of mandelbrot */
  return num_calculations;
} /* mandelbrot() */
