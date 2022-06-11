/*
 * Maxime Kotur, hw7.c, CS 24000, Fall 2018
 * Last updated October 11, 2018
 */

#include "hw7.h"

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define MIN_CHAR (32)

/*
 * This function takes a string and an integer. If the int is DUPLICATE then
 * "transform" the string into a linked list. If the int is REVERSE then
 * "transform" the string into a linked list in the reversed order.
 * Once the list has been created, traverse it and "transorm" it back into
 * a string. Finally, once the new string has been created, destory the linked
 * list and return a pointer to the new, NULL terminated string.
 * Asserts that the first argument is not null and the value pointed to it is
 * not either.
 * Asserts that the second argument is either DUPLICATE or REVERSE.
 * Returns a pointer to the new string created.
 */

char *copy_string(char *word, int operation) {
  assert(word != NULL);
  assert(*word != '\0');
  assert((operation == DUPLICATE) || (operation == REVERSE));
  struct node *head = NULL;
  if (operation == DUPLICATE) {
    head = string_to_list(word, NO);
  }
  if (operation == REVERSE) {
    head = string_to_list(word, YES);
  }
  int length = 0;
  while (word[length] != '\0') {
    length++;
  }
  char *string = list_to_string(head);
  free_list(head);
  return string;
} /* copy_string() */

/*
 * Calls append_char() or prepend_char() depending on the second argument and
 * allocates a node of the characters in the provided first string argument.
 * Append or prepend each node to the one holding the previous character.
 * This functions accepts a pointer to the string and an int reverse which
 * specifies if the string will be put in a list in reverse (YES) or not (NO).
 * Calls append_char() if no and prepend_char() if yes.
 * Asserts that the first argument is not null and the value pointed to it is
 * not either.
 * Returns a pointer to the head of the list.
 */

struct node *string_to_list(char *word, int reverse) {
  assert(word != NULL);
  assert(*word != '\0');
  assert((reverse == YES) || (reverse == NO));
  int length = 0;
  while (word[length] != '\0') {
    length++;
  }
  struct node *p = NULL;
  for (int i = 0; i < length; i++) {
    if (reverse == YES) {
      p = prepend_char(p, word[i]);
    }
    if (reverse == NO) {
      p = append_char(p, word[i]);
    }
  }
  return p;

} /* string_to_list() */

/*
 * Creates a node holding the character argument. Append it to the tail of the
 * list. This function accepts a pointer to the struct node and a character to
 * be appended to the list. If the first argument (if not NULL) will point to
 * the head of the list. If the first argument is NULL, the function should
 * assume that the function is appending to a new list.
 * Asserts that the character passed as an argument is not a control character.
 * Returns a pointer to the new list head.
 */

struct node *append_char(struct node *ptr, char value) {
  assert(value >= MIN_CHAR);
  struct node *temp = malloc(sizeof(struct node));
  assert(temp);
  temp->val = value;
  temp->next = NULL;
  if (ptr == NULL) {
    return temp;
  }
  else {
    struct node *head = ptr;
    while (head->next != NULL) {
      head = head->next;
    }
    head->next = temp;
    return ptr;
  }
} /* append_char() */

/*
 * Creates a node holding the character argument. Prepend it to the head of the
 * list. This function accepts a pointer to the struct node and a character to
 * be appended to the list. If the first argument (if not NULL) will point to
 * the head of the list. If the first argument is NULL, the function should
 * assume that the function is prepending to a new list.
 * Asserts that the character passed as an argument is not a control character.
 * Returns a pointer to the new list head.
 */

struct node *prepend_char(struct node *ptr, char value) {
  assert(value >= MIN_CHAR);
  struct node *head = malloc(sizeof(struct node));
  assert(head != NULL);
  head->val = value;
  if (ptr != NULL) {
    head->next = ptr;
  }
  else {
    head->next = NULL;
  }
  return head;
} /* prepend_char() */

/*
 * Allocates new memory for a character string of unknown length and traverses
 * the list to get the characters in order to copy them to the newly allocated
 * string. This function takes a pointer to the head of the list.
 * Asserts that the pointer is not NULL.
 * Returns a pointer to the character string allocated in this function.
 */

char *list_to_string(struct node *ptr) {
  assert(ptr);
  struct node *head = ptr;
  int length = 0;
  while (ptr != NULL) {
    ptr = ptr->next;
    length++;
  }
  char *string = malloc((length + 1) * sizeof(char));
  assert(string);
  int i = 0;
  while (i < length) {
    string[i] = head->val;
    head = head->next;
    i++;
  }
  string[length] = '\0';
  return string;
} /* list_to_string() */

/*
 * Traverses the list pointed by the arguments and deallocates all of the
 * nodes. Can take in NULL lists.
 * Has no Return value.
 */

void free_list(struct node *ptr) {
  if (ptr == NULL) {
    return;
  }
  else if (ptr->next == NULL) {
    free(ptr);
    ptr = NULL;
    return;
  }
  else {
    struct node *temp = NULL;
    while (ptr != NULL) {
      temp = ptr->next;
      free(ptr);
      ptr = temp;
    }
    return;
  }
} /* free_list() */

/*
 * Converts both strings passed in as arguments into two lists, joins the lists
 * into one and copies the elements of the new big list into a new string.
 * After deallocates the lists used. This functions takes two pointers to
 * strings and concatenates them.
 * Asserts that the first argument is not null and the value pointed to it is
 * not either.
 */

char *concat_strings(char *word_1, char *word_2) {
  assert(word_1 != NULL);
  assert(*word_1 != '\0');
  struct node *p_1 = NULL;
  struct node *p_2 = NULL;
  p_1 = string_to_list(word_1, NO);
  if (*word_2 != '\0') {
    p_2 = string_to_list(word_2, NO);
  }
  append_lists(p_1, p_2);
  int length = 0;
  while (word_1[length] != '\0') {
    length++;
  }
  while (word_2[length] != '\0') {
    length++;
  }
  char *string = list_to_string(p_1);
  free_list(p_1);
  return string;
} /* concat_strings() */

/*
 * Makes the tail of the first list point to the head of the second. This
 * function takes two pointer to struct node (list heads) as arguments and
 * appends the second list to the end of the first list.
 * If the second argument is NULL, don't do anything.
 * Asserts that the first argument is not NULL.
 * Has no Return value.
 */

void append_lists(struct node *ptr_1, struct node *ptr_2) {
  assert(ptr_1 != NULL);
  if (ptr_2 == NULL) {
    return;
  }
  struct node *head = ptr_1;
  while (ptr_1->next != NULL) {
    ptr_1 = ptr_1->next;
  }
  ptr_1->next = ptr_2;
  ptr_1 = head;
  return;
} /* append_lists() */
