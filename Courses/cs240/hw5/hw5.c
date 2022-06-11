/*
 * Maxime Kotur, hw5.c, CS 24000, Fall 2018
 * Last updated September 27, 2018
 */

/* Add Headers here */
#include "hw5.h"

/* Add #include here */
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* Add #define here */
#define BUFFER (100);

/* Add Global Values Here */
human_t g_human_array[MAX_HUMANS];
unsigned int g_human_count = 0;

/*
 * This function reads a list of humans from the file specified by the first
 * argument. The humans should be stored into the g_human_array from 0 until
 * the end of the file. Since the names are potentially longer than the space
 * for the names in the human_t stucture, it would be more preferable to use
 * temporary buffers to read the strings into.
 * Asserts that the first argument is not NULL.
 * Returns NON_READABLE_FILE if file is unreadable.
 * Returns READ_BAD_RECORD if any errors occur.
 * Returns the number of human records read from the input file if successful.
 */

int read_humans(char *filename) {
  assert(filename != NULL);
  FILE *file = fopen(filename, "r");
  int status = 0;
  if (file == NULL) {
    return NON_READABLE_FILE;
  }
  g_human_count = 0;
  while (!feof(file)) {
    human_t human;
    char last[BUFFER];
    char first[BUFFER];
    char mother_l[BUFFER];
    char mother_f[BUFFER];
    char father_l[BUFFER];
    char father_f[BUFFER];
    status = fscanf(file, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n,]\n",
                    last,
                    first,
                    mother_l,
                    mother_f,
                    father_l,
                    father_f);
    if (status != 6) {
      fclose(file);
      file = NULL;
      return READ_BAD_RECORD;
    }
    strncpy(human.last_name, last, NAME_LENGTH);
    strncpy(human.first_name, first, NAME_LENGTH);
    strncpy(human.mother_last, mother_l, NAME_LENGTH);
    strncpy(human.mother_first, mother_f, NAME_LENGTH);
    strncpy(human.father_last, father_l, NAME_LENGTH);
    strncpy(human.father_first, father_f, NAME_LENGTH);
    human.last_name[NAME_LENGTH-1] = '\0';
    human.first_name[NAME_LENGTH-1] = '\0';
    human.mother_last[NAME_LENGTH-1] = '\0';
    human.mother_first[NAME_LENGTH-1] = '\0';
    human.father_last[NAME_LENGTH-1] = '\0';
    human.father_first[NAME_LENGTH-1] = '\0';
    g_human_array[g_human_count] = human;
    g_human_count++;
  }
  fclose(file);
  file = NULL;
  return g_human_count;
} /* read_humans() */

/*
 * This function's purpose is to find if any children are stored in the
 * g_human_array and return its index. This function should go through
 * g_human_array to find all instances of human_t's where the full names
 * of either the mother or father match the search arguments. The function
 * should store the array index of a matching human in the array pointed by
 * the child_array.
 * The arguments last_name and first_name are the full name of the parent in
 * order to find the child. The argument child_array is the integer array
 * where the index of the children are found.
 * Asserts that all passed arguments are not NULL.
 * Returns zero if no parents are found.
 * Returns the number of children found if successful.
 */

int find_children(char *last_name, char *first_name, int *child_array) {
  assert(last_name != NULL);
  assert(first_name != NULL);
  assert(child_array != NULL);
  int child_count = 0;
  for (int i = 0; i < g_human_count; i++) {
    if (strncmp(g_human_array[i].father_last, last_name, NAME_LENGTH) == 0) {
      if (strncmp(g_human_array[i].father_first, first_name,
          NAME_LENGTH) == 0) {
        child_array[child_count] = i;
        child_count++;
        continue;
      }
    }
    if (strncmp(g_human_array[i].mother_last, last_name, NAME_LENGTH) == 0) {
      if (strncmp(g_human_array[i].mother_first, first_name,
          NAME_LENGTH) == 0) {
        child_array[child_count] = i;
        child_count++;
      }
    }
  }
  return child_count;
} /* find_children() */
