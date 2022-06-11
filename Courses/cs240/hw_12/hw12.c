/*
 * Maxime Kotur, hw12.c, CS 24000, Fall 2018
 * Last updated November 25, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc_debug.h>

#include "object.h"
#include "graphics.h"

#define COLOR_SIZE (7)

/*
 * Reads an object representation of a file and creates the object.
 */

object *read_object(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }
  fscanf(file, "%*s\n");
  object *obj = NULL;
  obj = malloc(sizeof(struct object));
  int status = fscanf(file, "%d %d\n", &obj->num_points, &obj->num_polygons);
  if (status != 2) {
    return NULL;
  }
  int count = 0;
  int start;
  int truth = 1;
  obj->points = malloc(sizeof(point) * obj->num_points);
  while (count != obj->num_points) {
    status = fscanf(file, "%d %lf %lf %lf\n",
                    &start,
                    &obj->points[count].arr[0],
                    &obj->points[count].arr[1],
                    &obj->points[count].arr[2]);
    if (status != 4) {
      return NULL;
    }
    if (start == 0) {
      truth = 0;
    }
    obj->points->arr[3] = 0;
    count++;
  }
  obj->polygons = malloc(sizeof(polygon) * obj->num_polygons);
  count = 0;
  char color[COLOR_SIZE];
  while (count != obj->num_polygons) {
    status = fscanf(file, "%*s %s %d",
                    color, &obj->polygons[count].num_points);
    if (status != 2) {
      return NULL;
    }
    int poly_count = 0;
    obj->polygons[count].point_arr = malloc(sizeof(point) *
      obj->polygons[count].num_points);
    while (poly_count != obj->polygons[count].num_points) {
      int num = 0;
      status = fscanf(file, "%d", &num);
      if (status != 1) {
        return NULL;
      }
      if (truth == 1) {
        num--;
      }
      obj->polygons[count].point_arr[poly_count] = &obj->points[num];
      if (poly_count == obj->polygons[count].num_points) {
        status = fscanf(file, "\n");
        if (status != 0) {
          return NULL;
        }
      }
      poly_count++;
    }
    Uint8 r = 'r';
    Uint8 g = 'g';
    Uint8 b = 'b';
    name_to_rgb(color, &r, &g, &b);
    obj->polygons[count].r = r;
    obj->polygons[count].g = g;
    obj->polygons[count].b = b;
    count++;
  }
  fclose(file);
  file = NULL;
  return obj;
} /* read_object() */

/*
 * Deallocates an object and everything it points to.
 */

void free_object(object *obj) {
  for (int i = obj->num_polygons - 1; i >= 0; i--) {
    if (obj->polygons[i].point_arr != NULL) {
      free(obj->polygons[i].point_arr);
      obj->polygons[i].point_arr = NULL;
    }
  }
  if (obj->polygons != NULL) {
    free(obj->polygons);
    obj->polygons = NULL;
  }
  if (obj->points != NULL) {
    free(obj->points);
    obj->points = NULL;
  }
  free(obj);
  obj = NULL;
  return;
} /* free_object() */
