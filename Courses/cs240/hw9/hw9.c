/*
 * Maxime Kotur, hw9.c, CS 24000, Fall 2018
 * Last updated October 25, 2018
 */

#include "hw9.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>

/*
 * Allocates adn assigns memory for the struct fields and the struct itself.
 * The next_ptr and prev_ptr should be initialized to NULL.
 * The double pointer is then assigned to the newmy created item.
 * Asserts that the pointer arguments are not NULL.
 * Asserts that no memory allocations are NULL.
 */

void create_double(double_list **ptr, char *first, char *last, int age) {
  assert(ptr != NULL);
  assert(first != NULL);
  assert(last != NULL);
  double_list *list = NULL;
  list = malloc(sizeof(double_list));
  assert(list);
  list->first_name = malloc(strlen(first) + 1);
  assert(list->first_name != NULL);
  strcpy(list->first_name, first);
  list->last_name = malloc(strlen(last) + 1);
  assert(list->last_name != NULL);
  strcpy(list->last_name, last);
  list->age = age;
  list->next_ptr = NULL;
  list->prev_ptr = NULL;
  (*ptr) = list;
  return;
} /* create_double() */

/*
 * Appends the solitary element to the list pointed to by the first argument.
 * Asserts that neither the first nor the second argument are NULL.
 * Asserts  that the second argument’s prev_ptr and next_ptr are NULL.
 */

void append_double(double_list **ptr, double_list *list) {
  assert(ptr != NULL);
  assert(list != NULL);
  assert(list->next_ptr == NULL);
  assert(list->prev_ptr == NULL);
  if (*ptr == NULL) {
    (*ptr) = list;
    return;
  }
  if ((*ptr)->next_ptr != NULL) {
    (*ptr)->next_ptr->prev_ptr = list;
  }
  list->next_ptr = (*ptr)->next_ptr;
  list->prev_ptr = (*ptr);
  (*ptr)->next_ptr = list;
  (*ptr) = list;
  return;
} /* append_double() */

/*
 * This function is just like append_double() except that it traverses the
 * list and puts the new element into the list in sorted order. The list is
 * ordered in ascending alphabetical order by last name, with the first name
 * used to break ties.
 * Asserts that neither the first nor the second argument are NULL.
 * Asserts  that the second argument’s prev_ptr and next_ptr are NULL.
 */

void insert_in_order(double_list **ptr, double_list *list) {
  assert(ptr != NULL);
  assert(list != NULL);
  assert(list->next_ptr == NULL);
  assert(list->prev_ptr == NULL);
  if ((*ptr) == NULL) {
    (*ptr) = list;
    return;
  }
  while ((*ptr)->prev_ptr != NULL) {
    (*ptr) = (*ptr)->prev_ptr;
  }
  while (*ptr != NULL) {
    int compare = strcmp((*ptr)->last_name, list->last_name);
    if (compare > 0) {
      if ((*ptr)->prev_ptr != NULL) {
        (*ptr)->prev_ptr->next_ptr = list;
      }
      list->prev_ptr = (*ptr)->prev_ptr;
      list->next_ptr = (*ptr);
      (*ptr)->prev_ptr = list;
      (*ptr) = list;
      return;
    }
    else if (compare < 0 ) {
      if ((*ptr)->next_ptr == NULL) {
        (*ptr)->next_ptr = list;
        list->prev_ptr = (*ptr);
        (*ptr) = list;
        return;
      }
      (*ptr) = (*ptr)->next_ptr;
    }
    else {
      compare = strcmp((*ptr)->first_name, list->first_name);
      if (compare > 0) {
        if ((*ptr)->prev_ptr != NULL) {
          (*ptr)->prev_ptr->next_ptr = list;
        }
        list->prev_ptr = (*ptr)->prev_ptr;
        list->next_ptr = (*ptr);
        (*ptr)->prev_ptr = list;
        (*ptr) = list;
        return;
      }
      else if (compare <= 0) {
        if ((*ptr)->next_ptr == NULL) {
          (*ptr)->next_ptr = list;
          list->prev_ptr = (*ptr);
          (*ptr) = list;
          return;
        }
        (*ptr) = (*ptr)->next_ptr;
      }
      else {
        return;
      }
    }
  }
  return;
} /* insert_in_order() */

/*
 * Removes a double_list specified by the second argument from the list which
 * is pointed by the double pointer.
 * Asserts that neither the first nor the second argument are NULL.
 */

void remove_double(double_list **ptr, double_list *list) {
  assert(ptr != NULL);
  assert(list != NULL);
  if (list->prev_ptr == NULL) {
    if (list->next_ptr != NULL) {
      list->next_ptr->prev_ptr = NULL;
      (*ptr) = list->next_ptr;
      list->next_ptr = NULL;
      return;
    }
  }
  else if (list->prev_ptr == NULL) {
    if (list->next_ptr == NULL) {
      *ptr = NULL;
      return;
    }
  }
  else {
    if (list->next_ptr != NULL) {
      list->next_ptr->prev_ptr = list->prev_ptr;
    }
    if (list->prev_ptr != NULL) {
      list->prev_ptr->next_ptr = list->next_ptr;
    }
    (*ptr) = list->prev_ptr;
    list->prev_ptr = NULL;
    list->next_ptr = NULL;
    return;
  }
} /* remove_double() */

/*
 * Deallocates the double pointer and the strings that its fields point to.
 * Sets the pointer that points to the next and previous structs to NULL.
 * Asserts that the argument is not NULL and that the pointer pointed to by
 * the argument is also not NULL.
 * Asserts  that the next_ptr and prev_ptr fields of the element to be
 * deleted are NULL.
 */

void delete_double(double_list **ptr) {
  assert(ptr != NULL);
  assert(*ptr != NULL);
  assert((*ptr)->next_ptr == NULL);
  assert((*ptr)->prev_ptr == NULL);
  free((*ptr)->last_name);
  free((*ptr)->first_name);
  free((*ptr));
  *ptr = NULL;
  return;
} /* delete_double() */

/*
 * Deallocates each element of the list. Does nothing if the argument is NULL.
 * This function calls the delete_double() function to simplify the operation.
 */

void delete_double_list(double_list **ptr) {
  assert(ptr != NULL);
  if ((*ptr) == NULL) {
    return;
  }
  while ((*ptr)->prev_ptr != NULL) {
    (*ptr) = (*ptr)->prev_ptr;
  }
  double_list *temp = (*ptr);
  while ((*ptr) != NULL) {
    temp = temp->next_ptr;
    (*ptr)->prev_ptr = NULL;
    (*ptr)->next_ptr = NULL;
    delete_double(ptr);
    (*ptr) = temp;
  }
  (*ptr) = NULL;
  return;
} /* delete_double_list() */
