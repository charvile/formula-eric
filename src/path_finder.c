#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "control.h"
#include "path_finder.h"
#include "utilities.h"



void find_shortest_path(struct node start, struct node finish, struct map *m)
{
    struct node current_node = start;

    printf("Start : (%f;%f)\nEnd : (%f;%f)\n", start.pos.x, start.pos.y, finish.pos.x, finish.pos.y);
    //int counter = 0;
    while (1)
    {
        g_map[current_node.i][current_node.j].type = '@';
        //current_node.type = 'V';
        if (vector_cmp(current_node.pos, finish.pos))
        {
            break;
        }
        //printf("Current node : (%f;%f)\n", current_node.pos.x, current_node.pos.y);
        //printf("Current node : (%d;%d)\n", current_node.i, current_node.j);
        g_map[current_node.i][current_node.j].open = 2;
        //current_node.open = 2;

        struct node *neighbors = malloc(sizeof(*neighbors) * 8);
        /* TODO : check return value here*/
        int index = 0;
        for (int a = -1; a <= 1; a++)
        {
            for (int b = -1; b <= 1; b++)
            {
                if (a == 0 && b == 0)
                {
                    continue;
                }

                if (current_node.i + a >= 0 && current_node.j + b >= 0 
                        && current_node.i + a < m->width
                        && current_node.j + b < m->width)
                {
                    printf("i :  %d | j = %d\n", current_node.i +a, current_node.j + b);
                    neighbors[index] = g_map[current_node.i + a][current_node.j + b];
                    //g_map[current_node.i + a][current_node.j + b].type = 'V';
                    g_map[current_node.i + a][current_node.j + b].open = 1;
                    if (neighbors[index].type == '#' || 
                        neighbors[index].type == '"' || 
                        neighbors[index].open == 2   || 
                        neighbors[index].open == 1)
                    {
                        continue;
                    }

                    //float g_cost = get_cost_vector(neighbors[index].pos, current_node.pos) + current_node.g_cost;
                    float g_cost = get_cost_vector(neighbors[index].pos, current_node.pos);
                    float h_cost = get_cost_vector(finish.pos, neighbors[index].pos);

                    neighbors[index].f_cost = g_cost + h_cost;
                    neighbors[index].g_cost = g_cost;
                    neighbors[index].h_cost = h_cost;

                    index++;
                }
            }
        }

        /* TODO: FIND MINIMUM*/ 
        struct node min_node = find_minimum(neighbors, index);
        //printf("Current node : (%d; %d)\n", current_node.i, current_node.j);
        //printf("New node : (%d; %d)\n", min_node.i, min_node.j);
        current_node = g_map[min_node.i][min_node.j];

        free(neighbors);
        //counter++;

    }   
}

struct node **map_init(struct map *m)
{
    int mwidth = m->width;
    int mheight = m->height;

    printf("width of the map %d \n", mwidth);
    printf("height of the map %d \n", mheight);
    printf("x start %f \n", m->start.x);
    printf("y start %f \n", m->start.y);

    struct node start;

    struct node finish;

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
                finish = nodes[i][j];
            }
            else if (j == floor(m->start.x) && i == floor(m->start.y))
            {
                nodes[i][j].type = 'S';
                start = nodes[i][j];
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
    puts("DISPLAYING SHORTEST PATH:");

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c", g_map[i][j].type);
        }
        fprintf(stdout,"\n");
    }
    return nodes;
}
