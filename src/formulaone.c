#include "control.h"
#include <math.h>
#include "path_finder.h"

int is_on_starting_point(struct car *car)
{
    if (car->position.x == map_get_start_x(car->map)
        && car->position.y == map_get_start_y(car->map))
    {
        return 1;
    }
    return 0;
}

static int is_facing_obj(struct car *car, enum floortype obj, int distance)
{
    //fprintf(stderr, "Car angle is : %f ; %f\n", car->direction.x, car->direction.y);
    int pos_x = car->position.x;
    int pos_y = car->position.y;

    int angle_x = floor(car->direction.x + CAR_TURN_ANGLE);
    int angle_y = floor(car->direction.y + CAR_TURN_ANGLE);

    //fprintf(stderr, "New car angle is : %d ; %d\n", angle_x, angle_y);

    if (map_get_floor(car->map, pos_x + angle_x * distance,
        pos_y + angle_y * distance) != obj)
    {
        return 0;
    }
    return 1;
}

int is_at_desired_angle(struct car *car, float angle);

enum move update(struct car *car)
{
    if (!map)
    {
        map = map_init(car->map);
    }
    if (is_facing_obj(car, ROAD, 1) && is_facing_obj(car, ROAD, 2))
    {
        //if (car->speed.x > 0.05f || car->speed.y > 0.05f)
        //{
            //return BRAKE;
        //}
        //return ACCELERATE;
    }
    else if (is_facing_obj(car, ROAD, 1) && !is_facing_obj(car, ROAD, 2))
    {
        return TURN_RIGHT;
    }
    {
        return TURN_RIGHT;
    }
    return BRAKE;
}
