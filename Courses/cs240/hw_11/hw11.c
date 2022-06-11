/*
 * Maxime Kotur, hw11.c, CS 24000, Fall 2018
 * Last updated November 12, 2018
 */

#include "hw11.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * This function prints out the values stored in a tree given
 * a pointer to the tree's root node.
 */

void print_tree(struct node *root) {
  if (!root) {
    return;
  }
  print_tree(root->left);
  print_node(root);
  print_tree(root->right);
} /* print_tree() */

/*
 * Deletes the whole tree and sets the root pointer to NULL.
 */

void delete_tree(struct node **root) {
  assert(root != NULL);
  while (1) {
    if ((*root) == NULL) {
      return;
    }
    else if ((*root)->left != NULL) {
      delete_tree(&(*root)->left);
      (*root)->left = NULL;
    }
    else if ((*root)->right != NULL) {
      delete_tree(&(*root)->right);
      (*root)->right = NULL;
    }
    else {
      ((*root)->delete)(&((*root)->data));
      free((*root));
      (*root) = NULL;
      root = NULL;
      return;
    }
  }
} /* delete_tree() */

/*
 * This function prints the values associated with a node's data.
 */

void print_node(struct node *n_ptr) {
  assert(n_ptr && n_ptr->data && n_ptr->print);
  (n_ptr->print)(n_ptr->data);
} /* print_node() */

/*
 * Dynamically allocates a struct node and initializes the pointers of the
 * node using the arguments given.
 */

void create_node(struct node **root, void *data, void (*print_node)(void *),
                 void (*delete_node)(void **),
                 int (*compare_node_data)(void *, void *)) {
  assert(root != NULL);
  assert((*root) == NULL);
  assert(data != NULL);
  assert(print_node != NULL);
  assert(delete_node != NULL);
  assert(compare_node_data != NULL);
  struct node *node = NULL;
  node = (struct node*)malloc(sizeof(struct node));
  assert(node != NULL);
  node->data = data;
  node->print = print_node;
  node->delete = delete_node;
  node->compare = compare_node_data;
  node->left = NULL;
  node->right = NULL;
  (*root) = node;
  return;
} /* create_node() */

/*
 * Deallocates the data field by calling the delete function by using the
 * delete function pointer and then frees the node itself.
 */

void delete_node(struct node **node) {
  assert(node != NULL);
  assert((*node) != NULL);
  assert((*node)->right == NULL);
  assert((*node)->left == NULL);
  ((*node)->delete)(&((*node)->data));
  free((*node));
  (*node) = NULL;
  node = NULL;
  return;
} /* delete_node() */

/*
 * Inserts the second argument into the tree by using the compare function
 * of the root pointer to make comparisons.
 */

void insert_node(struct node **root, struct node *tree) {
  assert(root != NULL);
  assert(tree != NULL);
  assert(tree->left == NULL);
  assert(tree->right == NULL);
  if ((*root) == NULL) {
    (*root) = tree;
    return;
  }
  if (((*root)->compare)(((*root)->data), (tree->data)) >= 0) {
    if ((*root)->left == NULL) {
      (*root)->left = tree;
      return;
    }
    else {
      insert_node(&(*root)->left, tree);
    }
  }
  else {
    if ((*root)->right == NULL) {
      (*root)->right = tree;
      return;
    }
    else {
      insert_node(&(*root)->right, tree);
    }
  }
} /* insert_node() */

/*
 * This function will dynamically allocate memory for an array of N struct
 * node pointers and fill it in with the addresses of the matching nodes.
 */

struct node **find_nodes(struct node *root, void *data, int *num_nodes) {
  assert(root != NULL);
  assert(data != NULL);
  assert(num_nodes != NULL);
  (*num_nodes) = 0;
  struct node *temp = NULL;
  temp = root;
  while (1) {
    if ((temp->compare)((temp->data), data) == 0) {
      (*num_nodes)++;
      temp = temp->left;
      while (temp != NULL) {
        if ((temp->compare)((temp->data), data) == 0) {
          (*num_nodes)++;
        }
        temp = temp->left;
      }
      break;
    }
    if ((temp->compare)((temp->data), data) > 0) {
      if (temp->left == NULL) {
        break;
      }
      temp = temp->left;
      continue;
    }
    if ((temp->compare)((temp->data), data) < 0) {
      if (temp->right == NULL) {
        break;
      }
      temp = temp->right;
    }
  }
  if ((*num_nodes) == 0) {
    return NULL;
  }
  struct node **array_of_dups = NULL;
  array_of_dups = (struct node **)malloc(sizeof(struct node *) * (*num_nodes));
  int count = 0;
  while (1) {
    if ((root->compare)((root->data), data) == 0) {
      array_of_dups[count++] = root;
      root = root->left;
      while (root != NULL) {
        if ((root->compare)((root->data), data) == 0) {
          array_of_dups[count++] = root;
        }
        root = root->left;
      }
      break;
    }
    if ((root->compare)((root->data), data) > 0) {
      if (root->left == NULL) {
        break;
      }
      root = root->left;
      continue;
    }
    if ((root->compare)((root->data), data) < 0) {
      if (root->right == NULL) {
        break;
      }
      root = root->right;
    }
  }
  return array_of_dups;
} /* find_nodes() */

/*
 * Removes the second argument from the tree by using the compare function
 * and relinks the tree in order to maintain the sortedness of the tree.
 */

void remove_node(struct node **root, struct node *tree) {
  assert(root != NULL);
  assert(tree != NULL);
  if ((((*root)->compare)(((*root)->data), (tree->data)) == 0)) {
    if (((*root)->left == tree->left) && ((*root)->right == tree->right)) {
      if (((*root)->left == NULL) && ((*root)->right == NULL)) {
        (*root) = NULL;
        return;
      }
      else if (((*root)->left != NULL) && ((*root)->right == NULL)) {
        struct node *temp = NULL;
        temp = (*root)->left;
        (*root)->left = NULL;
        (*root) = temp;
        return;
      }
      else if (((*root)->left == NULL) && ((*root)->right != NULL)) {
        struct node *temp = NULL;
        temp = (*root)->right;
        (*root)->right = NULL;
        (*root) = temp;
        return;
      }
      else {
        struct node *temp = NULL;
        temp = (*root)->right;
        struct node *hold = NULL;
        hold = (*root)->left;
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root) = hold;
        while ((*root)->right != NULL) {
          (*root) = (*root)->right;
        }
        (*root)->right = temp;
        (*root) = hold;
        return;
      }
    }
  }
  struct node *child = NULL;
  child = (*root);
  if ((child->compare)((child->data), (tree->data)) >= 0) {
    if (child->left == NULL) {
      return;
    }
    child = child->left;
  }
  else if ((child->compare)((child->data), (tree->data)) < 0) {
    if (child->right == NULL) {
      return;
    }
    child = child->right;
  }
  struct node *top = NULL;
  top = (*root);
  while (child != NULL) {
    if ((child->compare)((child->data), (tree->data)) == 0) {
      if ((child->left == tree->left) && (child->right == tree->right)) {
        if ((child->left == NULL) && (child->right == NULL)) {
          if ((*root)->left == child) {
            (*root)->left = NULL;
          }
          if ((*root)->right == child) {
            (*root)->right = NULL;
          }
          (*root) = top;
          return;
        }
        else if ((child->left != NULL) && (child->right == NULL)) {
          if ((*root)->left == child) {
            (*root)->left = child->left;
          }
          else if ((*root)->right == child) {
            (*root)->right = child->left;
          }
          child->left = NULL;
          (*root) = top;
          return;
        }
        else if ((child->left == NULL) && (child->right != NULL)) {
          if ((*root)->left == child) {
            (*root)->left = child->right;
          }
          else if ((*root)->right == child) {
            (*root)->right = child->right;
          }
          child->right = NULL;
          (*root) = top;
          return;
        }
        else {
          struct node *temp = NULL;
          temp = child->right;
          struct node *hold = NULL;
          hold = child->left;
          if ((*root)->left == child) {
            (*root)->left = child->left;
          }
          else if ((*root)->right == child) {
            (*root)->right = child->left;
          }
          child->left = NULL;
          child->right = NULL;
          child = hold;
          while (child->right != NULL) {
            child = child->right;
          }
          child->right = temp;
          (*root) = top;
          return;
        }
      }
    }
    if ((child->compare)((child->data), (tree->data)) >= 0) {
      if (child->left == NULL) {
        return;
      }
      (*root) = child;
      child = child->left;
      continue;
    }
    if ((child->compare)((child->data), (tree->data)) < 0) {
      if (child->right == NULL) {
        return;
      }
      (*root) = child;
      child = child->right;
      continue;
    }
  }
  return;
} /* remove_node() */

/*
 * This function prints the values associated with a person.
 */

void print_person_data(void *person) {
  struct person *person_ptr = (struct person *) person;
  assert(person_ptr && person_ptr->first_name &&
         person_ptr->last_name && person_ptr->occupation);
  printf("%15s %15s %15s %4d %9d\n",
         person_ptr->first_name, person_ptr->last_name, person_ptr->occupation,
         person_ptr->age, person_ptr->ssn);
} /* print_person_data() */

/*
 * Creates a person node, allocates the appropriate memory for the necessary
 * fields, and populates the fields by copying the arguments into the
 * structure.
 */

void create_person_data(void **person_ptr, const char *first, const char *last,
                        const char *occup, int age, int ssn) {
  assert(person_ptr != NULL);
  assert((*person_ptr) == NULL);
  assert(first != NULL);
  assert(last != NULL);
  assert(occup != NULL);
  struct person *person = NULL;
  person = malloc(sizeof(struct person));
  assert(person);
  person->first_name = malloc(strlen(first) + 1);
  assert(person->first_name != NULL);
  strcpy(person->first_name, first);
  person->last_name = malloc(strlen(last) + 1);
  assert(person->last_name != NULL);
  strcpy(person->last_name, last);
  person->occupation = malloc(strlen(occup) + 1);
  assert(person->occupation != NULL);
  strcpy(person->occupation, occup);
  person->age = age;
  person->ssn = ssn;
  (*person_ptr) = (void *)person;
  return;
} /* create_person_data() */

/*
 * Deallocates the memory for the relevant fields. Then deallocates the node
 * itself and sets the pointer to NULL.
 */

void delete_person_data(void **person_ptr) {
  assert(person_ptr != NULL);
  assert((*person_ptr) != NULL);
  struct person **person = (struct person **) person_ptr;
  free((*person)->first_name);
  free((*person)->last_name);
  free((*person)->occupation);
  free((*person));
  (*person) = NULL;
  person = NULL;
  person_ptr = NULL;
  return;
} /* delete_person_data() */

/*
 * Compares the ssn fields of the person structures passed in.
 */

int compare_person_data(void *person_1, void *person_2) {
  assert(person_1 != NULL);
  assert(person_2 != NULL);
  struct person *person_1p = (struct person *) person_1;
  struct person *person_2p = (struct person *) person_2;
  if (person_1p->ssn > person_2p->ssn) {
    return 1;
  }
  else if (person_1p->ssn < person_2p->ssn) {
    return -1;
  }
  else {
    return 0;
  }
} /* compare_person_data() */

/*
 * This function prints the values associated with a student.
 */

void print_student_data(void *student) {
  struct student *student_ptr = (struct student *)student;
  assert(student_ptr && student_ptr->first_name &&
         student_ptr->last_name && student_ptr->college);
  printf("%15s %15s %15s %3.2f %9d\n",
         student_ptr->first_name, student_ptr->last_name, student_ptr->college,
         student_ptr->gpa, student_ptr->id);
} /* print_student_data() */

/*
 * Creates a student node, allocates the appropriate memory for the necessary
 * fields, and populates the fields by copying the arguments into the
 * structure.
 */

void create_student_data(void **student_ptr, const char *first,
                         const char *last, const char *coll,
                         float gpa, int id) {
  assert(student_ptr != NULL);
  assert((*student_ptr) == NULL);
  assert(first != NULL);
  assert(last != NULL);
  assert(coll != NULL);
  struct student *student = NULL;
  student = malloc(sizeof(struct student));
  assert(student);
  student->first_name = malloc(strlen(first) + 1);
  assert(student->first_name != NULL);
  strcpy(student->first_name, first);
  student->last_name = malloc(strlen(last) + 1);
  assert(student->last_name != NULL);
  strcpy(student->last_name, last);
  student->college = malloc(strlen(coll) + 1);
  assert(student->college != NULL);
  strcpy(student->college, coll);
  student->gpa = gpa;
  student->id = id;
  (*student_ptr) = (void *)student;
  return;
} /* create_student_data() */

/*
 * Deallocates the memory for the relevant fields. Then deallocates the node
 * itself and sets the pointer to NULL.
 */

void delete_student_data(void **student_ptr) {
  assert(student_ptr != NULL);
  assert((*student_ptr) != NULL);
  struct student **student = (struct student **) student_ptr;
  free((*student)->first_name);
  free((*student)->last_name);
  free((*student)->college);
  free((*student));
  (*student) = NULL;
  student = NULL;
  student_ptr = NULL;
  return;
} /* delete_student_data() */

/*
 * Compares the id fields of the student structures passed in.
 */

int compare_student_data(void *student_1, void *student_2) {
  assert(student_1 != NULL);
  assert(student_2 != NULL);
  struct student *student_1s = (struct student *) student_1;
  struct student *student_2s = (struct student *) student_2;
  if (student_1s->id > student_2s->id) {
    return 1;
  }
  else if (student_1s->id < student_2s->id) {
    return -1;
  }
  else {
    return 0;
  }
} /* compare_student_data() */
