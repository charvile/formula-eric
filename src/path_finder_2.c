#include "path_finder.h"
#include "utilities.h"
#include <stdlib.h>

void draw_best_path(struct node start, struct node finish)
{
    struct node current = finish;

    while(current.pos.x != start.pos.x && current.pos.y != start.pos.y)
    {
        current = g_map[current.previous->i][current.previous->j]; 
        g_map[current.i][current.j].type = '-';
    }
}

void set_checkpoints(struct node start, struct node finish)
{
    struct node current = start;

    float current_angle = 0;
    int count = 0;
    while(!vector_cmp(current.pos, finish.pos))
    {
        if (count == 0)
        {
            current_angle = get_angle_vector(current.pos, 
                current.previous->pos);
        }

        float angle = get_angle_vector(current.pos, current.next->pos);

        if (angle != current_angle)
        {
            current.type = 'C';
            current_angle = angle;
        }
        count++;
    }
}

void destroy_map(int size)
{
    for (int i = 0; i < size; i++)
    {
        free(g_map[i]);
    }

    free(g_map);
}
