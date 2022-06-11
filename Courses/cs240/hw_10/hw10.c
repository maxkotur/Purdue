/*
 * Maxime Kotur, hw10.c, CS 24000, Fall 2018
 * Last updated November 1, 2018
 */

#include "hw10.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>

/*
 * Allocates memory for a tree structure, the name field and the title field.
 * Copies the arguments, sets all arguments to the tree. The left_ptr and
 * right_ptr are initialized to NULL.
 * Asserts that the pointer arguments and memory allocations are not NULL.
 * Returns a pointer to the newly allocated element.
 */

tree *tree_create(char *tree_name, char *tree_title, unsigned int id) {
  assert(tree_name != NULL);
  assert(tree_title != NULL);
  tree *tree = NULL;
  tree = (struct tree*)malloc(sizeof(struct tree));
  assert(tree != NULL);
  tree->name = malloc(strlen(tree_name) + 1);
  assert(tree->name != NULL);
  strcpy(tree->name, tree_name);
  tree->title = malloc(strlen(tree_title) + 1);
  assert(tree->title != NULL);
  strcpy(tree->title, tree_title);
  tree->id_number = id;
  tree->right_ptr = NULL;
  tree->left_ptr = NULL;
  return tree;
} /* tree_create() */

/*
 * Inserts the tree argument into the binary tree using recursion.
 * The insertion occurs accordingly to the name field.
 * Asserts that neither the first nor the second argument is NULL;
 * Asserts that the second argument’s left_ptr and right_ptr fields are NULL.
 */

void tree_insert(tree **root, tree *tree) {
  assert(root != NULL);
  assert(tree != NULL);
  assert(tree->left_ptr == NULL);
  assert(tree->right_ptr ==  NULL);
  if ((*root) == NULL) {
    (*root) = tree;
    return;
  }
  if (strcmp((*root)->name, tree->name) >= 0) {
    if ((*root)->left_ptr == NULL) {
      (*root)->left_ptr = tree;
      return;
    }
    else {
      tree_insert(&(*root)->left_ptr, tree);
    }
  }
  else {
    if ((*root)->right_ptr == NULL) {
      (*root)->right_ptr = tree;
      return;
    }
    else {
      tree_insert(&(*root)->right_ptr, tree);
    }
  }
} /* tree_insert() */

/*
 * This recursive function will search for a tree node whose name
 * field matches the second argument.
 * Asserts that the second argument is not NULL.
 * Returns a pointer to the node if a matching node is found otherwise NULL.
 */

tree *tree_find(tree *tree, char *tree_name) {
  assert(tree_name != NULL);
  if (tree == NULL) {
    return NULL;
  }
  if (strcmp(tree->name, tree_name) == 0) {
    return tree;
  }
  if (strcmp(tree->name, tree_name) > 0) {
    return tree_find(tree->left_ptr, tree_name);
  }
  return tree_find(tree->right_ptr, tree_name);
} /* tree_find() */

/*
 * Deletes the entire tree and its name and title fields recursively. Before
 * returning, the root of the tree is set to NULL.
 * Asserts that the first argument is not NULL.
 */

void tree_delete(tree **root) {
  assert(root != NULL);
  while (1) {
    if ((*root) == NULL) {
      return;
    }
    else if ((*root)->left_ptr != NULL) {
      tree_delete(&(*root)->left_ptr);
      (*root)->left_ptr = NULL;
    }
    else if ((*root)->right_ptr != NULL) {
      tree_delete(&(*root)->right_ptr);
      (*root)->right_ptr = NULL;
    }
    else {
      free((*root)->name);
      free((*root)->title);
      free((*root));
      (*root) = NULL;
      *root = NULL;
      return;
    }
  }
} /* tree_delete() */
