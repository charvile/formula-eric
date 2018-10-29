#ifndef STEERING_H
#define STEERING_H
#include "control.h"

enum move get_next_action(struct car *car);

int is_at_desired_angle(struct car *car, float angle);

float get_distance_to_next_checkpoint(struct car *car); /* DEFINE MACRO FOR SLOWING DOWN DISTANCE + MAX_SPEED */

float get_angle_at_next_checkpoint(struct car *car);

#endif /* ! STEERING_H */
