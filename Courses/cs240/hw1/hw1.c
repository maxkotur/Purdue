/* Maxime Kotur, hw1.c, CS 24000, Fall 2018
 * Last updated August 30, 2018
 */

/* Add any includes here */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hw1.h"

/* Define check here (to see if record line is correct)*/
int check(char record[]){
  int length = 0;
  while (record[length] != '\0') {
    length++;
  }
  
  /* see if section number is a digit*/
  if (!isdigit(record[length-1])) {
    return BAD_RECORD;
  }

  int semi1;
  int semi2;
  int semi3;
  int num_of_semi = 0;
  /*parsing through record line*/
  for (int i = 0; i < length; i++) {
    if (record[i] == ';') {
      num_of_semi++;
      if (num_of_semi == 1) {
        semi1 = i;
      }
      if (num_of_semi == 2) {
        semi2 = i;
      }
      if (num_of_semi == 3) {
        semi3 = i;
      }
    }
  }
  if (num_of_semi != 3) {
    return BAD_RECORD;
  }
  if (record[semi3-1] != '%') {
    return BAD_RECORD;
  }
  if (semi1+1 > MAX_NAME_LEN) {
    return BAD_RECORD;
  }

  /* see if the id is an int*/
  for (int i = semi1+1; i < semi2; i++) {
    if (!isdigit(record[i])) {
      return BAD_RECORD;
    }
  }

  /* see if the score is an int*/
  for (int i = semi2+1; i < semi3-1; i++) {
    if (!isdigit(record[i])) {
      return BAD_RECORD;
    }
  }

  return OK;
}


/* Define get_section_average here */
float get_section_average(char *filename, int section_num){
  if (section_num < 1 || section_num > 9) {
    return BAD_SECTION;
  }
  FILE *file;
  file = fopen(filename, "r");
  char line[100];
  int scores[100] = {0};
  int num_of_students = 0;
  int status = 0;
  if (file != NULL) {
    /*fscanf that returns the whole line*/
    while ((status = fscanf(file, "%[^\n]%*c", line)) != -1) {
      int length = 0;
      while (line[length] != '\0') {
        length++;
      }

      if (check(line) == BAD_RECORD) {
        fclose(file);
        file = NULL;
        return BAD_RECORD;
      }

      /*if wrong section number, then skip to next line*/
      if (atoi(&line[length-1]) != section_num) {
        continue;
      }
      /*parsing through record line*/
      char score[3] = {0};
      int num_of_semi = 0;
      int start_of_score;
      int end_of_score;
      for (int i = 0; i < length; i++) {
        if (line[i] == ';') {
          num_of_semi++;
          if (num_of_semi == 2) {
            start_of_score = i+1;
          }
        }
        if (line[i] == '%') {
          end_of_score = i-1;
        }
      }

      /*getting the score of record line*/
      if (start_of_score == end_of_score) {
        score[0] = line[start_of_score];
      }
      else if(end_of_score - start_of_score == 1){
        score[0] = line[start_of_score];
        score[1] = line[end_of_score];
      }
      else if(end_of_score - start_of_score == 2){
        score[0] = line[start_of_score];
        score[1] = line[start_of_score+1];
        score[2] = line[end_of_score];
      }
      scores[num_of_students] = atoi(score);
      num_of_students++;
    }
    fclose(file);
    file = NULL;

    int sum = 0;
    for (int i = 0; i < num_of_students; i++) {
      sum+= scores[i];
    }
    if (num_of_students == 0) {
      return NO_STUDENTS;
    }
    float average = sum*1.0/num_of_students;
    return average;
  }
  else{
    return FILE_READ_ERR;
    }
  }

/* Define get_top_score here */
  int get_top_score(char *filename){
    FILE *file;
    file = fopen(filename, "r");
    char line[100];
    int status = 0;
    int best_score = 0;
    if (file != NULL) {
      /*fscanf that returns the whole line*/
      while ((status = fscanf(file, "%[^\n]%*c", line)) != -1) {

        int length = 0;
        while (line[length] != '\0') {
          length++;
        }

        if (check(line) == BAD_RECORD) {
          fclose(file);
          file = NULL;
          return BAD_RECORD;
        }

        /*parsing through record*/
        char score[3] = {0};
        int num_of_semi = 0;
        int start_of_score;
        int end_of_score;
        for (int i = 0; i < length; i++) {
          if (line[i] == ';') {
            num_of_semi++;
            if (num_of_semi == 2) {
              start_of_score = i+1;
            }
          }
          if (line[i] == '%') {
            end_of_score = i-1;
          }
        }
        /*getting the score*/
        if (start_of_score == end_of_score) {
          score[0] = line[start_of_score];
        }
        else if(end_of_score - start_of_score == 1){
          score[0] = line[start_of_score];
          score[1] = line[end_of_score];
        }
        else if(end_of_score - start_of_score == 2){
          score[0] = line[start_of_score];
          score[1] = line[start_of_score+1];
          score[2] = line[end_of_score];
        }
        /*finding the best score*/
        if (atoi(score) > best_score) {
          best_score = atoi(score);
        }
      }
      fclose(file);
      file = NULL;
      return best_score;
    }
    else{
      return FILE_READ_ERR;
    }
  }
/* Define create_fail_list here */
  int create_fail_list(char *in_file, char *out_file, int cutoff){
    if (cutoff <= 0 || cutoff >= 100) {
      return BAD_CUTOFF;
    }
    FILE *in;
    in = fopen(in_file, "r");
    if (in == NULL) {
      return FILE_READ_ERR;
    }
    FILE *out;
    out = fopen(out_file, "w");
    if (out == NULL) {
      fclose(in);
      in = NULL;
      return FILE_WRITE_ERR;
    }
    char line[100];
    int student_num;
    int status = 0;
    int num_of_failed = 0;
    /*fscanf that returns the whole line*/
    while ((status = fscanf(in, "%[^\n]%*c", line)) != -1) {

      int length=0;
      while (line[length] != '\0') {
        length++;
      }

      if (check(line) == BAD_RECORD) {
        fclose(in);
        in = NULL;
        fclose(out);
        out = NULL;
        return BAD_RECORD;
      }

      student_num = atoi(&line[length-1]);

      int num_of_semi = 0;
      int end_of_name;
      int start_of_score = 0;
      int end_of_score = 0;
      int start_of_id;
      int end_of_id;
      /*parsing through record line*/
      for (int i = 0; i < length; i++) {
        if (line[i] == ';') {
          num_of_semi++;
          if (num_of_semi == 1) {
            end_of_name = i;
            start_of_id = i+1;
          }
          if (num_of_semi == 2) {
            start_of_score = i+1;
            end_of_id = i;
          }
          if (num_of_semi == 3) {
            end_of_score = i-1;
          }
        }
      }
      /*getting the score*/
      int summed = 0;
      for (int i = start_of_score; i < end_of_score; i++) {
        summed*=10;
        summed += line[i]-'0';
      }
      /*getting the name*/
      char name[MAX_NAME_LEN] = {0};
      for (int i = 0; i < end_of_name; i++) {
        name[i] = line[i];
      }
      /*getting the id*/
      char id[100] = {0};
      int j = 0;
      for (int i = start_of_id; i < end_of_id; i++) {
        id[j] = line[i];
        j++;
      }
      int num_id = atoi(id);

      /*finding scores under cutoff*/
      if (summed < cutoff) {
        fprintf(out, "%d - %d - %s\n", student_num, num_id, name);
        num_of_failed++;
      }
    }
    fclose(out);
    out = NULL;
    fclose(in);
    in = NULL;
    if (num_of_failed == 0) {
      return NO_STUDENTS;
    }
    return num_of_failed;
  }
/* Define create_grade_report here */
  int create_grade_report(char *in_file, char *out_file, int section_num){
    if (section_num < 1 || section_num > 9) {
      return BAD_SECTION;
    }
    FILE *in;
    in = fopen(in_file, "r");
    if (in == NULL) {
      return FILE_READ_ERR;
    }
    FILE *out;
    out = fopen(out_file, "w");
    if (out == NULL) {
      fclose(in);
      in = NULL;
      return FILE_WRITE_ERR;
    }
    char line[100];
    int student_num;
    int status = 0;
    int num_of_graded = 0;
    /*fscanf that returns the whole line*/
    while ((status = fscanf(in, "%[^\n]%*c", line)) != -1) {

      int length = 0;
      while (line[length] != '\0') {
        length++;
      }

      if (check(line) == BAD_RECORD) {
        fclose(in);
        in = NULL;
        fclose(out);
        out = NULL;
        return BAD_RECORD;
      }

      student_num = atoi(&line[length-1]);
      /*if wrong section number, then skip to next line*/
      if (student_num != section_num) {
        continue;
      }

      int num_of_semi = 0;
      int start_of_score;
      int end_of_score;
      int start_of_id;
      int end_of_id;
      /*parsing though the record line*/
      for (int i = 0; i < length; i++) {
        if (line[i] == ';') {
          num_of_semi++;
          if (num_of_semi == 1) {
            start_of_id = i+1;
          }
          if (num_of_semi == 2) {
            start_of_score = i+1;
            end_of_id = i;
          }
          if (num_of_semi == 3) {
            end_of_score = i-1;
          }
        }
      }

      /*getting the score*/
      int summed = 0;
      for (int i = start_of_score; i < end_of_score; i++) {
        summed*=10;
        summed += line[i]-'0';
      }

      /*getting the id*/
      char id[100] = {0};
      int j = 0;
      for (int i = start_of_id; i < end_of_id; i++) {
        id[j] = line[i];
        j++;
      }

      /*associating scores with grades*/
      if (summed >= 90) {
        fprintf(out, "%s: A\n", id);
        num_of_graded++;
      }
      else if (summed >= 80) {
        fprintf(out, "%s: B\n", id);
        num_of_graded++;
      }
      else if (summed >= 70) {
        fprintf(out, "%s: C\n", id);
        num_of_graded++;
      }
      else if (summed >= 60) {
        fprintf(out, "%s: D\n", id);
        num_of_graded++;
      }
      else if (summed < 60) {
        fprintf(out, "%s: F\n", id);
        num_of_graded++;
      }
    }
    fclose(out);
    out = NULL;
    fclose(in);
    in = NULL;

    if (num_of_graded == 0) {
      return NO_STUDENTS;
    }
    return num_of_graded;
  }
/* Remember, you don't need a main function!
 * it is provided by hw1_main.c or hw1_test.o
 */
