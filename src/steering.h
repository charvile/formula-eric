#ifndef STEERING_H
#define STEERING_H
#include "control.h"

enum move get_next_action(struct car *car);

int is_at_desired_angle(struct car *car);

float get_distance_to_next_checkpoint(struct car *car);

float get_angle_at_next_checkpoint(struct car *car);

struct node *get_current_position(struct car *car);

int get_car_degree(struct car *car);

#endif /* ! STEERING_H */
