#include "steering.h"
#include "utilities.h"
#include "path_finder.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SLOW_DOWN_DISTANCE 0.5
#define MAX_SPEED 0.05

static int is_on_finish(struct car *car)
{
    //printf("Type is %c\n", get_current_position(car)->type);
    return get_current_position(car)->type == 'F';
}

enum move get_next_action(struct car *car)
{
    float distance_to_checkpoint = get_distance_to_next_checkpoint(car);
    //struct node *p= get_current_position(car);
    //int car_angle = get_car_degree(car);
    //int desired_angle = round(get_angle_at_next_checkpoint(car) * (180 / M_PI));

    //printf("Car is on matrix : %d;%d\n", p->j, p->i);
    printf("Car is on position : %f;%f\n", car->position.x, car->position.y);
    //printf("Car angle :%d\n", car_angle);
    //printf("Desired angle :%d\n", desired_angle);

    /*TODO:check if next checkpoint is arrive:if true, accelerate like crazy*/
    //printf("Distance to next checkpoint : %f\n", distance_to_checkpoint);
    if (is_on_finish(car))
    {
        puts("ARRIVED ON FINISH");
    }
    if (is_at_desired_angle(car))
    {
        //puts("AT DESIRED ANGLE");
        if (car->speed.x != 0 && distance_to_checkpoint <= SLOW_DOWN_DISTANCE)
        {
            return BRAKE;
        }
        else if (car->speed.x == 0 && distance_to_checkpoint
            <= SLOW_DOWN_DISTANCE)
        {
            if (car->speed.x || car->speed.y> MAX_SPEED)
            {
                return BRAKE;
            }
            return ACCELERATE;
        }
        if (distance_to_checkpoint > SLOW_DOWN_DISTANCE)
        {
            if (car->speed.x || car->speed.y> MAX_SPEED)
            {
                return BRAKE;
            }
            return ACCELERATE;
        }
    }
    else if (car->speed.x > 0)
    {
        return BRAKE;
    }
    else
    {
        //puts("NOT AT DESIRED ANGLE");
        //if (car_angle == 0)
        //{
          //  car_angle = 360;
        //}
        //float diff_angle = abs(car_angle - desired_angle);
        //printf("Desired angle :%d\n", desired_angle);
        //printf("Car angle :%d\n\n", abs(car_angle));
        //if (diff_angle < 180)
        //{
          //  return TURN_LEFT;
        //}*/
	if (turn_left(car))
	{
		return TURN_LEFT;
	}
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
    //printf("Car position x:%f y:%f\n", x, y);
    return &g_map[j][i];
}

int is_at_desired_angle(struct car *car)
{
    int desired_angle = round(get_angle_at_next_checkpoint(car) * (180 / M_PI));
    desired_angle %= 360;
    //printf("Desired angle is %d\n", desired_angle);
    int car_angle = get_car_degree(car);
    //printf("Car angle is %d\n", car_angle);
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
        return get_cost_vector(car->position, next_checkpoint->pos) + 0.5;
    }
    return 0;
}

int get_car_degree(struct car *car)
{
    float degrees = (car->direction_angle * (180 / M_PI));
    int ret = round(degrees);
    ret = (ret + 360) % 360;
    return ret;
}

float get_angle_at_next_checkpoint(struct car *car)
{
    struct node *cur = get_current_position(car);

    if (!cur->next_checkpoint)
    {
        puts("DID NOT FIND CHECKPOINT");
        return 0;
    }
    struct node *nxt = &g_map[cur->next_checkpoint->i][cur->next_checkpoint->j];
    struct vector2 cur_pos_x_y = car->position;

    if (!nxt)
    {
        return 0;
    }
    else
    {
       return get_abs_angle_2_pts(cur_pos_x_y, nxt->pos);
    }
}

int turn_left(struct car *car)
{
    struct node *cur = get_current_position(car);
    if (!cur->next_checkpoint)
    {
	return 1;
    }
    struct node *nxt = &g_map[cur->next_checkpoint->i][cur->next_checkpoint->j];
    struct vector2 cur_pos_x_y = car->position;
    struct vector2 car_direction = car->direction;
    struct vector2 desired_direction = make_vector(cur_pos_x_y, nxt->pos);
    if (det(car_direction, desired_direction) < 0)
    {
	return 1;
    }
    return 0;
}
