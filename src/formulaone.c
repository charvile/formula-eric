#include "control.h"
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
    //fprintf(stderr, "Car angle is : %f ; %f\n", car->direction.x, car->direction.y);
    int pos_x = car->position.x;
    int pos_y = car->position.y;

    int angle_x = floor(car->direction.x + CAR_TURN_ANGLE);
    int angle_y = floor(car->direction.y + CAR_TURN_ANGLE);

    //fprintf(stderr, "New car angle is : %d ; %d\n", angle_x, angle_y);

    if (map_get_floor(car->map, pos_x + angle_x, pos_y + angle_y) != ROAD)
    {
        return 0;
    }
    return 1;
}

static int is_facing_road_long_term(struct car *car)
{
    int pos_x = car->position.x;
    int pos_y = car->position.y;

    int angle_x = floor(car->direction.x + CAR_TURN_ANGLE);
    int angle_y = floor(car->direction.y + CAR_TURN_ANGLE);

    if (map_get_floor(car->map, pos_x + angle_x * 2, pos_y + angle_y * 2) != ROAD)
    {
        return 0;
    }
    return 1;
}

enum move update(struct car *car)
{
    if (is_facing_road(car) && is_facing_road_long_term(car))
    {
        //if (car->speed.x > 0.05f || car->speed.y > 0.05f)
        //{
            //return BRAKE;
        //}
        return ACCELERATE;
    }
    else if (is_facing_road(car) && !is_facing_road_long_term(car))
    {
        return TURN_RIGHT;
    }
    {
        return TURN_RIGHT;
    }
    return BRAKE;
}
