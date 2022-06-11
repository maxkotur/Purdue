/*
 * Maxime Kotur, hw4.c, CS 24000, Fall 2018
 * Last updated September 21, 2018
 */

/* Add Headers here */
#include "hw4.h"

/* Add #include here */
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Add Global Values here */
student_t g_student_array[MAX_STUDENTS];
unsigned int g_student_count = 0;

/*
 * This function reads a list of students form the file specified by the
 * first argument. The students are stored into g_student_array.
 * char *filename is the name of the file.
 * Asserts that file is not NULL.
 * Returns NON_READABLE_FILE when file is unreadable.
 * Returns READ_BAD_RECORD when reads an incorrect file.
 * Returns g_student_count, number of students in the record, if successful.
 */

int read_students(char *filename) {
  assert(filename != NULL);
  FILE *file = fopen(filename, "r");
  int status = 0;
  if (file == NULL) {
    return NON_READABLE_FILE;
  }
  g_student_count = 0;
  while (!feof(file)) {
    student_t student;
    char class;
    status = fscanf(file, "%u,%[^,],%[^,],%c,$%f,%hu,%s\n",
                    &student.id_number,
                    student.last_name,
                    student.first_name,
                    &class,
                    &student.money,
                    &student.dorm_room,
                    student.schedule[0]);
    if (class == 'U') {
      student.classification = UNDERGRADUATE;
    }
    else if (class == 'G') {
      student.classification = GRADUATE;
    }
    else {
      fclose(file);
      file = NULL;
      return READ_BAD_RECORD;
    }
    for (int i = 0; i < DAYS; i++) {
      for (int j = 0; j < HOURS; j++) {
        if (student.schedule[i][j] == '0') {
          student.schedule[i][j] = 0;
        }
      }
    }
    if (status != 7) {
      fclose(file);
      file = NULL;
      return READ_BAD_RECORD;
    }
    g_student_array[g_student_count] = student;
    g_student_count++;
  }
  fclose(file);
  file = NULL;
  return g_student_count;
} /* read_students() */

/*
 * This function writes a list of students into the file specified by the
 * first argument. The second argument is the number of entries in the
 * student array to write into the file.
 * char *filename is the name of the file.
 * int num_entries is the number of entries.
 * Asserts that the file is not NULL.
 * Asserts that the number of entries is non-negative.
 * Returns NON_WRITABLE_FILE when file is unwriteable.
 * Returns the number of student records written if successful.
 */

int write_students(char *filename, int num_entries) {
  assert(filename != NULL);
  assert(num_entries >= 0);
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return NON_WRITABLE_FILE;
  }
  for (int i = 0; i < num_entries; i++) {
    for (int j = 0; j < DAYS; j++) {
      for (int k = 0; k < HOURS; k++) {
        if (g_student_array[i].schedule[j][k] == 0) {
          g_student_array[i].schedule[j][k] = '0';
        }
      }
    }
  }
  for (int i = 0; i < num_entries; i++) {
    char full_schedule[51];
    int count = 0;
    for (int j = 0; j < DAYS; j++) {
      for (int k = 0; k < HOURS; k++) {
        full_schedule[count] = g_student_array[i].schedule[j][k];
        count++;
      }
    }
    full_schedule[count] = '\0';
    char class;
    if (g_student_array[i].classification == UNDERGRADUATE) {
      class = 'U';
    }
    else if (g_student_array[i].classification == GRADUATE) {
      class = 'G';
    }
    fprintf(file, "%u,%s,%s,%c,$%.2f,%hu,%s\n",
                    g_student_array[i].id_number,
                    g_student_array[i].last_name,
                    g_student_array[i].first_name,
                    class,
                    g_student_array[i].money,
                    g_student_array[i].dorm_room,
                    full_schedule);
  }
  fclose(file);
  file = NULL;
  return num_entries;
} /* write_students() */

/*
 * This function searches a student based on their id number.
 * unsigned int id is the id number to find the student.
 * Returns NOT_FOUND if not successful.
 * Returns the array index of the student if found.
 */

int find_student_by_id(unsigned int id) {
  for (int i = 0; i < g_student_count; i++) {
    if (g_student_array[i].id_number == id) {
      return i;
    }
  }
  return NOT_FOUND;
} /* find_student_by_id() */

/*
 * This function seaches a student based on their first name and their
 * last name. If multiple student entries are found with the same name,
 * the function should return the lowest numbered index.
 * char *first is to find the first name of the student.
 * char *last is to find the last name of the student.
 * Asserts that the neither argument is NULL.
 * Returns NOT_FOUND if no student can be found.
 * Return the lowest number index of the student array if successful.
 */

int find_student_by_name(char *first, char *last) {
  assert(first != NULL);
  assert(last != NULL);
  for (int i = 0; i < g_student_count; i++) {
    if (strcmp(g_student_array[i].first_name, first) == 0) {
      if (strcmp(g_student_array[i].last_name, last) == 0) {
        return i;
      }
    }
  }
  return NOT_FOUND;
} /* find_student_by_name() */

/*
 * This function calculates and returns the percentage of the student
 * body that is classified as an Undergraduate.
 * Returns the percentage of students who are Undergraduates.
 */

float compute_undergraduate_percent() {
  float num_undergraduate = 0;
  float percentage = 0;
  for (int i = 0; i < g_student_count; i++) {
    if (g_student_array[i].classification == UNDERGRADUATE) {
      num_undergraduate++;
    }
  }
  percentage = (num_undergraduate*100)/g_student_count;
  return percentage;
} /* compute_undergraduate_percent() */

/*
 * This function finds the student with the least amount of money,
 * subtracts one dollar fomr everyone's account, and adds it to
 * the poorest student's account.
 * Returns NOT_FOUND if two or more students are tied for being the poorest.
 * Returns the index of the poorest student if successful.
 */

int grant_scholarship() {
  float poorest = g_student_array[0].money;
  int index_poorest = 0;
  for (int i = 1; i < g_student_count; i++) {
    if (g_student_array[i].money < poorest) {
      poorest = g_student_array[i].money;
      index_poorest = i;
    }
  }
  for (int i = 0; i < g_student_count; i++) {
    if (poorest == g_student_array[i].money && i != index_poorest) {
      return NOT_FOUND;
    }
  }
  for (int i = 0; i < g_student_count; i++) {
    if (i == index_poorest) {
      continue;
    }
    g_student_array[i].money -= 1;
    g_student_array[index_poorest].money++;
  }
  return index_poorest;
} /* grant_scholarship() */

/*
 * This function scans through the student array and finds a dorm room that
 * contains three or more people.
 * Returns NOT_FOUND if no such room is found.
 * Returns the lowest numbered dorm room number of this kind.
 */

int find_full_dorm_room() {
  int full_dorms[g_student_count];
  for (int i = 0; i < g_student_count; i++) {
    int count = 0;
    for (int j = 0; j < g_student_count; j++) {
      if (g_student_array[i].dorm_room == g_student_array[j].dorm_room) {
        count++;
        full_dorms[i] = count;
      }
    }
  }
  int lowest = DORMS+1;
  for (int i = 1; i < g_student_count; i++) {
    if (g_student_array[i].dorm_room < lowest && full_dorms[i] >= 3) {
      lowest = g_student_array[i].dorm_room;
    }
  }
  if (lowest == DORMS+1) {
    return NOT_FOUND;
  }
  return lowest;
} /* find_full_dorm_room() */

/*
 * This function accepts the id numbers of two students in the student
 * array and finds the first time during the week where they do not have
 * a schedule conflict.
 * unsigned int id_1 and unsigned id_2 are the id numbers of both students.
 * Returns NOT_FOUND if one of the students isn't found on the student array.
 * Returns NOT_SCHEDULABLE if no time during the week where they do not have
 * a schedule conflict exists.
 * Returns the day of the week times 100 plus the hour of the day
 * if successful.
 */

unsigned int find_earliest_meeting(unsigned int id_1, unsigned int id_2) {
  int index_id_1 = -1;
  int index_id_2 = -1;
  for (int i = 0; i < g_student_count; i++) {
    if (g_student_array[i].id_number == id_1) {
      index_id_1 = i;
    }
    if (g_student_array[i].id_number == id_2) {
      index_id_2 = i;
    }
  }
  if (index_id_1 == -1 || index_id_2 == -1) {
    return NOT_FOUND;
  }
  for (int i = 0; i < DAYS; i++) {
    for (int j = 0; j < HOURS; j++) {
      if (g_student_array[index_id_1].schedule[i][j] == '0') {
        g_student_array[index_id_1].schedule[i][j] = 0;
      }
      if (g_student_array[index_id_2].schedule[i][j] == '0') {
        g_student_array[index_id_2].schedule[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < DAYS; i++) {
    for (int j = 0; j < HOURS; j++) {
      if (g_student_array[index_id_1].schedule[i][j] == 0) {
        if (g_student_array[index_id_2].schedule[i][j] == 0) {
          return i*100+j+7;
        }
      }
    }
  }
  return NOT_SCHEDULABLE;
} /* find_earlist_meeting() */
