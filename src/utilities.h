#ifndef UTILITIES_H
#define UTILITIES_H
#include "path_finder.h"

float get_distance(float x1, float x2, float y1, float y2);

float get_angle(float x1, float x2, float y1, float y2);

float get_angle_vector(struct vector2 v1, struct vector2 v2);

float get_cost(float x, float y, struct vector2 v);

float get_cost_vector(struct vector2 v1, struct vector2 v2);

struct node find_minimum(struct node *neighbors, int size);

int vector_cmp(struct vector2 v1, struct vector2 v2);

#endif /* ! UTILITIES_H */
