#include "path_finder.h"

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

    while(current.pos.x != finish.pos.x && current.pos.y != finish.pos.y)
    {

    }
}

void destroy_map(void);