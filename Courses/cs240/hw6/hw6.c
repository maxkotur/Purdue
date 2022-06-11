/*
 * Maxime Kotur, hw6.c, CS 24000, Fall 2018
 * Last updated October 4, 2018
 */

 #include "hw6.h"

 #include <stdio.h>
 #include <assert.h>
 #include <string.h>

 #define BUFFER (100)

 human_t g_human_array[MAX_HUMANS];
 unsigned int g_human_count;

 /*
  * This function reads a list of humans from the file specified by the first
  * argument. The humans should be stored into the g_human_array from 0 until
  * the end of the file. Since the names are potentially longer than the space
  * for the names in the human_t stucture, it would be more preferable to use
  * temporary buffers to read the strings into. Every pointer fields in the
  * human_t element of the g_human_array should be set to NULL.
  * Asserts that the first argument is not NULL.
  * Returns NON_READABLE_FILE if file is unreadable.
  * Returns READ_BAD_RECORD if any errors occur.
  * Returns the number of human records read from the input file if successful.
  */

int read_humans(char *filename) {
  assert(filename != NULL);
  FILE *file = fopen(filename, "r");
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
    int status = fscanf(file, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n,]\n",
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
    human.last_name[NAME_LENGTH - 1] = '\0';
    human.first_name[NAME_LENGTH - 1] = '\0';
    human.mother_last[NAME_LENGTH - 1] = '\0';
    human.mother_first[NAME_LENGTH - 1] = '\0';
    human.father_last[NAME_LENGTH - 1] = '\0';
    human.father_first[NAME_LENGTH - 1] = '\0';
    human.father_ptr = NULL;
    human.mother_ptr = NULL;
    human.child_ptr = NULL;
    human.sibling_ptr = NULL;
    g_human_array[g_human_count] = human;
    g_human_count++;
  }
  fclose(file);
  file = NULL;
  return g_human_count;
} /* read_humans() */

/*
* This function accepts no values and returns no values. This function should
* traverse the values in the g_human_array and find the mother, father,
* children and sibling for each element.
* If one of these are found, the value's pointers should be set accordingly.
* If a human doesn't have one of these, then the pointer for that value
* should remain as NULL.
* If multiple children are found then the lowest index child should be set as
* the child pointer.
* If multiple siblings are found then the sibling should point to each other
* from lowest index to highest index, making the highest index sibling remain
* as NULL.
*/

void establish_family() {
  for (int i = 0; i < g_human_count; i++) {
    for (int j = 0; j < g_human_count; j++) {
      if (strncmp(g_human_array[i].mother_last,
          g_human_array[j].last_name, NAME_LENGTH) == 0) {
        if (strncmp(g_human_array[i].mother_first,
            g_human_array[j].first_name, NAME_LENGTH) == 0) {
          g_human_array[i].mother_ptr = &g_human_array[j];
        }
      }
      if (strncmp(g_human_array[i].father_last,
          g_human_array[j].last_name, NAME_LENGTH) == 0) {
        if (strncmp(g_human_array[i].father_first,
            g_human_array[j].first_name, NAME_LENGTH) == 0) {
          g_human_array[i].father_ptr = &g_human_array[j];
        }
      }
    }
  }
  for (int i = 0; i < g_human_count; i++) {
    int child_check = 0;
    for (int j = 0; j < g_human_count; j++) {
      for (int k = 0; k < g_human_count; k++) {
        if (strncmp(g_human_array[i].last_name,
            g_human_array[k].father_last, NAME_LENGTH) == 0) {
          if (strncmp(g_human_array[i].first_name,
              g_human_array[k].father_first, NAME_LENGTH) == 0) {
            if (strncmp(g_human_array[j].last_name,
                g_human_array[k].mother_last, NAME_LENGTH) == 0) {
              if (strncmp(g_human_array[j].first_name,
                  g_human_array[k].mother_first, NAME_LENGTH) == 0) {
                if (child_check == 0) {
                  g_human_array[i].child_ptr = &g_human_array[k];
                  g_human_array[j].child_ptr = &g_human_array[k];
                  child_check++;
                }
              }
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < g_human_count; i++) {
    int sibling_check = 0;
    for (int j = 0; j < g_human_count; j++) {
      if (strncmp(g_human_array[i].father_last,
          g_human_array[j].father_last, NAME_LENGTH) == 0) {
        if (strncmp(g_human_array[i].father_first,
            g_human_array[j].father_first, NAME_LENGTH) == 0) {
          if (strncmp(g_human_array[i].mother_last,
              g_human_array[j].mother_last, NAME_LENGTH) == 0) {
            if (strncmp(g_human_array[i].mother_first,
                g_human_array[j].mother_first, NAME_LENGTH) == 0) {
              if (i < j) {
                if (sibling_check == 0) {
                  g_human_array[i].sibling_ptr = &g_human_array[j];
                  sibling_check++;
                }
              }
            }
          }
        }
      }
    }
  }
} /* establish_family() */
