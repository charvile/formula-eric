#include "steering.h"
#include "path_finder.h"
#include <math.h>
#include <stdio.h>

#define SLOW_DOWN_DISTANCE 2
#define MAX_SPEED 0.25

enum move get_next_action(struct car *car);

struct node *get_current_position(struct car *car)
{
    int i = floor(car->position.x);
    int j = floor(car->position.y);

    printf("Car is on tile %d;%d\n", i, j);
    return &g_map[i][j];
}

int is_at_desired_angle(struct car *car, float angle);

float get_distance_to_next_checkpoint(struct car *car);

float get_angle_at_next_checkpoint(struct car *car);

