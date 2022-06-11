/*
 * Maxime Kotur, hw8.c, CS 24000, Fall 2018
 * Last updated October 18, 2018
 */

#include "hw8.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>

/*
 * Dynamically allocate memory for a single_list structure. Allocate memory
 * for the first_name, and copy the first argument into it. Allocate memory
 * for the last_name and fill it with a copy of the second argument. Set
 * the age field to the last argument. The next_ptr should be initialized
 * to NULL.
 * Asserts that the char* arguments are not NULL.
 * Asserts that no memory allocations are NULL.
 * Returns the single_list created.
 */

single_list *create_single(char *first, char *last, int age) {
  assert(first != NULL);
  assert(last != NULL);
  single_list *single = NULL;
  single = malloc(sizeof(single_list));
  assert(single != NULL);
  single->first_name = malloc(strlen(first) + 1);
  assert(single->first_name != NULL);
  strcpy(single->first_name, first);
  single->last_name = malloc(strlen(last) + 1);
  assert(single->last_name != NULL);
  strcpy(single->last_name, last);
  single->age = age;
  single->next_ptr = NULL;
  return single;
} /* create_single() */

/*
 * Just like create_single() except that you allocate a double_list and
 * initialize the prev_ptr to NULL.
 * Asserts that the char* arguments are not NULL.
 * Asserts that no memory allocations are NULL.
 * Returns the single_list created.
 */

double_list *create_double(char *first, char *last, int age) {
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
  return list;
} /* create_double() */

/*
 * The first argument points to a single_list structure that is an element
 * of a singly-linked list. The second arguments points to a solitary
 * single_list structure whose next_ptr field is NULL. Append the solitary
 * element to the list element pointed to by the first argument.
 * Asserts that neither the first nor the second argument is NULL.
 * Asserts that the second argument's next_ptr is NULL.
 * Has no return value.
 */

void append_single(single_list *list, single_list *append) {
  assert(list);
  assert(append);
  assert(append->next_ptr == NULL);
  append->next_ptr = list->next_ptr;
  list->next_ptr = append;
  return;
} /* append_single() */

/*
 * The first argument points to a double_list structure that is an element
 * of a doubly-linked list. The second arguments points to a solitary
 * double_list structure whose next_ptr field is NULL. Append the solitary
 * element to the list element pointed to by the first argument.
 * Asserts that neither the first nor the second argument is NULL.
 * Asserts that the second argument's next_ptr is NULL.
 * Has no return value.
 */

void append_double(double_list *list, double_list *append) {
  assert(list);
  assert(append);
  assert(append->next_ptr == NULL);
  if (list->next_ptr != NULL) {
    list->next_ptr->prev_ptr = append;
  }
  append->next_ptr = list->next_ptr;
  list->next_ptr = append;
  append->prev_ptr = list;
  return;
} /* append_double() */

/*
 * The argument is a pointer to a singly-linked list. Form a doubly-linked
 * list with the same number of elements and contents as the singly-linked
 * list, and return a pointer to it. If the argument is NULL, return NULL.
 * The singly-linked list should remain intact and unchanged throughout the
 * function call and after it returns. This function should call your
 * create_double() and append_double() function to simplify the operation.
 * Returns the head of the double_list created.
 */

double_list *single_to_double(single_list *list) {
  if (list == NULL) {
    return NULL;
  }
  single_list *temp = NULL;
  temp = list;
  double_list *head = NULL;
  double_list *append = NULL;
  head = create_double(temp->first_name, temp->last_name, temp->age);
  temp = temp->next_ptr;
  while (temp != NULL) {
    append = create_double(temp->first_name, temp->last_name, temp->age);
    append_double(head, append);
    head = head->next_ptr;
    temp = temp->next_ptr;
  }
  while (head->prev_ptr != NULL) {
    head = head->prev_ptr;
  }
  return head;
} /* single_to_double() */

/*
 * The argument points to a single_list structure. Deallocate it and the
 * strings that its fields point to. Do not deallocate the structure
 * pointed to by next_ptr.
 * Asserts that the argument is not NULL.
 * Has no return value.
 */

void delete_single(single_list *list) {
  assert(list);
  if (list->first_name != NULL) {
    free(list->first_name);
  }
  list->first_name = NULL;
  if (list->last_name != NULL) {
    free(list->last_name);
  }
  list->last_name = NULL;
  free(list);
  return;
} /* delete_single() */

/*
 * Just like delete_single() except that it will deallocate a double_list
 * structure and the strings it points to. Do not deallocate the
 * structures pointed to by next_ptr or prev_ptr.
 * Asserts that the argument is not NULL.
 * Has no return value.
 */

void delete_double(double_list *list) {
  assert(list);
  if (list->first_name != NULL) {
    free(list->first_name);
  }
  list->first_name = NULL;
  if (list->last_name != NULL) {
    free(list->last_name);
  }
  list->last_name = NULL;
  free(list);
  return;
} /* delete_double() */

/*
 * The first argument points to a singly-linked list. Deallocate each
 * element of the list. It is not an error for the argument to be NULL. If
 * it is NULL, there is nothing to do. This function should call
 * delete_single() function to simplify the operation.
 * Has no return value.
 */

void delete_single_list(single_list *list) {
  if (list == NULL) {
    return;
  }
  single_list *temp = NULL;
  while (list != NULL) {
    temp = list->next_ptr;
    delete_single(list);
    list = temp;
  }
  return;
} /* delete_single_list() */

/*
 * The first argument points to a doubly-linked list. Deallocate each
 * element of the list. It is not an error for the argument to be NULL. If
 * it is NULL, there is nothing to do. This function should call
 * delete_double() function to simplify the operation.
 * Has no return value.
 */

void delete_double_list( double_list *list) {
  if (list == NULL) {
    return;
  }
  double_list *temp = NULL;
  while (list != NULL) {
    temp = list->next_ptr;
    delete_double(list);
    list = temp;
  }
  return;
} /* delete_double_list() */
