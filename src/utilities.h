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

float scalar_product(struct vector2 V1, struct vector2 V2);

float get_angle_3_pts(struct vector2 P1, struct vector2 P2, struct vector2 P3);

float get_abs_angle_2_pts(struct vector2 P1, struct vector2 P2);


#endif /* ! UTILITIES_H */
