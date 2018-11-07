#include "steering.h"
#include "utilities.h"
#include "path_finder.h"
#include <math.h>
#include <stdio.h>

#define SLOW_DOWN_DISTANCE 1
#define MAX_SPEED 0.25

enum move get_next_action(struct car *car)
{
    float distance_to_checkpoint = get_distance_to_next_checkpoint(car);
    /* TODO : check if next checkpoint is arrive : if true, accelerate like crazy*/
    if (is_at_desired_angle(car))
    {
        puts("AT DESIRED ANGLE");
        printf("Distance to next checkpoint : %f\n", distance_to_checkpoint);
        if (car->speed.x != 0 && distance_to_checkpoint <= SLOW_DOWN_DISTANCE)
        {
            return BRAKE;
        }
        else if (car->speed.x == 0 && distance_to_checkpoint <= SLOW_DOWN_DISTANCE)
        {
            if (car->speed.x > MAX_SPEED)
            {
                return BRAKE;
            }
            return ACCELERATE;
        }
        /* TODO : control speed here*/
        if (distance_to_checkpoint > SLOW_DOWN_DISTANCE)
        {
            if (car->speed.x > MAX_SPEED)
            {
                return BRAKE;
            }
            return ACCELERATE;
        }
    }
    else
    {
        return TURN_RIGHT;
    }

    return DO_NOTHING;
}

struct node *get_current_position(struct car *car)
{
    float x = car->position.x;
    int i = floor(x);
    float y = car->position.y;
    int j = floor(y);
    printf("Car position x:%f y:%f\n", x, y);
    return &g_map[j][i];
}

int is_at_desired_angle(struct car *car)
{
    /* TODO : implement this function */
    int desired_angle = round(get_angle_at_next_checkpoint(car) *(180 / M_PI));
    printf("Desired angle is %d\n", desired_angle);
    int car_angle = get_car_degree(car);
    printf("Car angle is %d\n", car_angle); 
    return desired_angle == car_angle;
}

float get_distance_to_next_checkpoint(struct car *car)
{
    struct node *current = get_current_position(car);
    struct node *next_checkpoint = current->next_checkpoint;

    if (!next_checkpoint)
    {
        puts("Cannot load next checkpoint");
    }
    else
    {
        return get_cost_vector(car->position, next_checkpoint->pos);
    }
    return 0;
}

int get_car_degree(struct car *car)
{
    float degrees = (car->direction_angle * (180 / M_PI));
    int ret = round(degrees);
    ret %= 360;
    return ret;
}

float get_angle_at_next_checkpoint(struct car *car)
{
    struct node *current = get_current_position(car);
    struct node *next = &g_map[current->next_checkpoint->i][current->next_checkpoint->j];
    //struct node *following = &g_map[next->next_checkpoint->i][next->next_checkpoint->j];

    //printf("Current is: %d;%d\n", current->i, current->j);
    //printf("Next is: %d;%d\n", next->i, next->j);
    //printf("Following is: %d;%d\n", following->i, following->j);
    //putchar('\n');


    if (!next)
    {
        //puts("Cannot load next checkpoint");
        return 0;
    }
    //else if (!following)
    //{
        //puts("Cannot load following checkpoint");
    //    return 0;
    //}
    else
    {

       return get_abs_angle_2_pts(current->pos, next->pos);
    }
}
