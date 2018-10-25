#include "path_finder.h"

void draw_best_path(struct node start, struct node finish)
{
    struct node current = finish;

    while(current.pos.x != start.pos.x && current.pos.y != start.pos.y)
    {
        current = g_map[current.previous->j][current.previous->j]; 
    }
}
