#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "control.h"
#include "path_finder.h"
#include "utilities.h"

void find_shortest_path(struct node *start, struct node *finish, struct map *m)
{
    struct list_node *list_open = init_list(start);
    while (1)
    {

        struct node *current_node = start = pop_list(list_open)->node;
        remove_list(list_open, current_node);
        //printf("Current node is : %d;%d\n", current_node->i, current_node->j);
        //printf("Size of open is : %zu\n", list_open->size);
        current_node->open = 2;

        if (vector_cmp(current_node->pos, finish->pos))
        {
            break;
        }
        int size = 0;

        struct node *neighbors = find_neighbors(current_node, &size, m, finish);
        for (int i = 0; i < size; i++)
        {
            if (neighbors[i].type == '#' ||
                    neighbors[i].type == '"' ||
                    neighbors[i].open == 2)
            {
                continue;
            }

            float new_path = neighbors[i].g_cost;
            float current_path = current_node->g_cost;

            if (new_path < current_path || neighbors[i].open == 0)
            {
                //neighbors[i].f_cost = get_cost_vector();
                neighbors[i].previous = current_node;
                g_map[neighbors[i].i][neighbors[i].j].previous = current_node;
                if (neighbors[i].open == 0)
                {
                    //printf("Adding %d;%d to the open list\n", neighbors[i].i, neighbors[i].j);
                	g_map[neighbors[i].i][neighbors[i].j].open = 1;
                    list_open = insert(list_open, &neighbors[i]);
                }
            }

        }
    }
}
