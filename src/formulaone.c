#include "control.h"
#include <stdio.h>
#include <math.h>

int is_on_starting_point(struct car *car)
{
    if (car->position.x == map_get_start_x(car->map)
        && car->position.y == map_get_start_y(car->map))
    {
        return 1;
    }
    return 0;
}


static int is_facing_road(struct car *car)
{
    fprintf(stderr, "Car angle is : %f ; %f\n", car->direction.x, car->direction.y);
    int pos_x = car->position.x;
    int pos_y = car->position.y;

    int angle_x = floor(car->direction.x);
    int angle_y = floor(car->direction.y);
    if (map_get_floor(car->map, pos_x + angle_x, pos_y + angle_y) != ROAD)
    {
        car->direction.x = angle_x;
        car->direction.y = angle_y;
        return 0;
    }
    return 1;
}

enum move update(struct car *car)
{
    if (is_on_starting_point(car))
    {
        if (!is_facing_road(car))
        {
            return TURN_RIGHT;
        }
        else
        {
            return ACCELERATE_AND_TURN_LEFT;
        }
    }

    if (is_facing_road(car))
    {
        return ACCELERATE;
    }
    else
    {
        return TURN_RIGHT;
    }
    return BRAKE;
}
