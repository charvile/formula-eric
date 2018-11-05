#include "steering.h"
#include "utilities.h"
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

    return &g_map[j][i];
}

int is_at_desired_angle(struct car *car, float angle);

float get_distance_to_next_checkpoint(struct car *car)
{
    struct node *current = get_current_position(car);
    struct node *next_checkpoint = current->next_checkpoint;

    if (!current->next_checkpoint)
    {
        puts("Cannot load next checkpoint");
    }
    else
    {
        return get_cost_vector(car->position, next_checkpoint->pos);
    }
    return 0;
}

float get_angle_at_next_checkpoint(struct car *car);
