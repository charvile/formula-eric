#include "control.h"
#include <math.h>
#include "path_finder.h"
#include <stdio.h>
#include <stdlib.h>

struct node **map_init(struct map *m)
{
    int mwidth = m->width;
    int mheight = m->height;

    struct node *start;

    struct node *finish;

    struct node **nodes = malloc(sizeof(void *) * mheight);


    for (int i = 0; i < mheight; i++)
    {
        nodes[i] = malloc(sizeof(struct node) * mwidth);
        for (int j = 0; j < mwidth; j++)
        {
            nodes[i][j].open = 0;
            nodes[i][j].pos.x = j + 0.5;
            nodes[i][j].pos.y = i + 0.5;
            nodes[i][j].i = i;
            nodes[i][j].j = j;
            if (map_get_floor(m, j, i) == FINISH)
            {
                nodes[i][j].type = 'F';
                finish = &nodes[i][j];
            }
            else if (j == floor(m->start.x) && i == floor(m->start.y))
            {
                nodes[i][j].type = 'S';
                start = &nodes[i][j];
            }
            else if (map_get_floor(m, j, i) == BLOCK)
            {
                nodes[i][j].type = '#';
            }
            else if (map_get_floor(m, j, i) == GRASS)
            {
                nodes[i][j].type = '"';
            }
            else
            {
                nodes[i][j].type = (map_get_floor(m, j, i) == ROAD) + '0';
            }
        }
    }
    g_map = nodes;

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c",nodes[i][j].type);
        }
        fprintf(stdout,"\n");
    }

    find_shortest_path(start, finish, m);
    draw_best_path(start, finish);
    puts("DISPLAYING SHORTEST PATH:");

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c", g_map[i][j].type);
        }
        fprintf(stdout,"\n");
    }
    puts("DONE");
    return nodes;
}
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
    if (!g_map)
    {
        map_init(car->map);
    }
    //printf("Car angle is %.2f; %.2f\n", car->direction.x, car->direction.y);
    if (is_facing_obj(car, ROAD, 1) && is_facing_obj(car, ROAD, 2))
    {
        //if (car->speed.x > 0.05f || car->speed.y > 0.05f)
        //{
          //  return BRAKE;
        //}
        return ACCELERATE;
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
