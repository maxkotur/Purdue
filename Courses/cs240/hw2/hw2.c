/*
 * Maxime Kotur, hw2.c, CS 24000, Fall 2018
 */

#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define any global variables here */
int g_product_count = 0;
char g_product_name[MAX_RECORDS][MAX_PRODUCT_LEN];
float g_unit_price[MAX_RECORDS];
int g_availability[MAX_RECORDS][STORES];

/* Define your functions here */

/*
 * input_tables function
 */

int input_tables(char *filename){
  FILE *file = fopen(filename, "r");
  int status = 0;
  if (file == NULL) {
    return FILE_READ_ERROR;
  }
  g_product_count = 0;
  while (!feof(file)) {
    status = fscanf(file, "%[^,],$%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                  g_product_name[g_product_count],
                  &g_unit_price[g_product_count],
                  &g_availability[g_product_count][0],
                  &g_availability[g_product_count][1],
                  &g_availability[g_product_count][2],
                  &g_availability[g_product_count][3],
                  &g_availability[g_product_count][4],
                  &g_availability[g_product_count][5],
                  &g_availability[g_product_count][6],
                  &g_availability[g_product_count][7],
                  &g_availability[g_product_count][8],
                  &g_availability[g_product_count][9]);
    g_product_count++;
    if (status != 12) {
      fclose(file);
      file = NULL;
      return RECORD_ERROR;
    } /* Checks for errors in record */
  } /* Scanning through the file */

  fclose(file);
  file = NULL;
  return g_product_count;
} /* input_tables() */

/*
 * unit_price function
 */

float unit_price(char *product_name){
  int price_index = -1;
  for (int i = 0; i < g_product_count; i++) {
    if (strcmp(g_product_name[i], product_name) == 0) {
      price_index = i;
      break;
    }
  } /* Looping through g_product_name to find product */
  if (price_index == -1) {
    return NO_SUCH_PRODUCT;
  } /* If price_index is still -1 then no product */
  return g_unit_price[price_index];
} /* unit_price() */

/*
 * net_worth function
 */

float net_worth(int store_num) {
  if (store_num < 0 || store_num > 9) {
    return OUT_OF_BOUNDS;
  }
  float net = 0;
  for (int i = 0; i < g_product_count; i++) {
    float mult = g_unit_price[i]*g_availability[i][store_num];
    net += mult;
  } /* Calculating net worth */
  return net;
} /* net_worth() */

/*
 * max_net_product function
 */

float max_net_product(int store_num) {
  if (store_num < 0 || store_num > 9) {
    return OUT_OF_BOUNDS;
  }
  float max_net = 0;
  for (int i = 0; i < g_product_count; i++) {
    float mult = g_unit_price[i]*g_availability[i][store_num];
    if (mult > max_net) {
      max_net = mult;
    } /* Calculating maximum net product */
  }
  return max_net;
} /* max_net_product() */

/*
 * max_prod_availability function
 */

int max_prod_availability(char *product_name){
  /* Looping through g_product_name to find product */
  int name_index = -1;
  for (int i = 0; i < g_product_count; i++) {
    if (strcmp(g_product_name[i], product_name) == 0) {
      name_index = i;
      break;
    }
  }
  if (name_index == -1) {
    return NO_SUCH_PRODUCT;
  } /* If name_index is still -1 then no product */
  float max_prod = 0;
  int store_num = 0;
  for (int i = 0; i < STORES; i++) {
    float prod = g_availability[name_index][i];
    if (prod > max_prod) {
      max_prod = prod;
      store_num = i;
    }
  } /* Calculates max product availability for the product */

  return store_num;
} /* max_prod_availability() */

/*
 * max_store_availability function
 */

int max_store_availability(int store_num){
  if (store_num < 0 || store_num > 9) {
    return OUT_OF_BOUNDS;
  }
  int max_store = 0;
  int max_index = 0;
  for (int i = 0; i < g_product_count; i++) {
    if (g_availability[i][store_num] > max_store) {
      max_store = g_availability[i][store_num];
      max_index = i;
    }
  } /* Calculates max store availability */
  return max_index;
} /* max_store_availability() */

/*
 * output_tables function
 */

int output_tables(char *filename, int start, int end){
  if (start < 0 || start > 9) {
    return OUT_OF_BOUNDS;
  }
  if (end < 0 || end > 9) {
    return OUT_OF_BOUNDS;
  }
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return FILE_WRITE_ERROR;
  }
  for (int i = 0; i < g_product_count; i++) {
    fprintf(file, "%s,$%.2f", g_product_name[i], g_unit_price[i]);
    for (int j = start; j < end+1; j++) {
      fprintf(file, ",%d", g_availability[i][j]);
      if (j == end) {
        fprintf(file, "\n");
      }
    }
  } /* Printing output */
  fclose(file);
  file = NULL;
  return OK;
} /* output_tables() */
