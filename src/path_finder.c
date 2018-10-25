#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "control.h"
#include "path_finder.h"

float get_distance(float x1, float x2, float y1, float y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

float get_angle(float x1, float x2, float y1, float y2)
{
    //printf("x1 : %f\nx2: %f\ny1: %f\ny2 : %f\n", x1, x2, y1, y2);
    float slope = (y2 - y1) / (x2 - x1);
    //printf("Slope is %f\n", slope);
    return atanf(slope);
}

float get_angle_vector(struct vector2 v1, struct vector2 v2)
{
    return get_angle(v1.x, v2.x, v1.y, v2.y);
}

float get_cost(float x, float y, struct vector2 v)
{
    return get_distance(x, v.x, y, v.y);
}

float get_cost_vector(struct vector2 v1, struct vector2 v2)
{
    return get_distance(v1.x, v2.x, v1.y, v2.y);
}

void find_shortest_path(struct node start, struct node finish, struct map *m)
{
    struct node current_node = start;
    printf("Start : (%f;%f)\nEnd : (%f;%f)\n", start.pos.x, start.pos.y, finish.pos.x, finish.pos.y);
    //int counter = 0;
    while (1)
    {
        map[current_node.i][current_node.j].type = 'V';
        //current_node.type = 'V';
        if ((current_node.pos.x != finish.pos.x && current_node.pos.y != finish.pos.y))
        {
            break;
        }
        printf("Current node : (%f;%f)\n", current_node.pos.x, current_node.pos.y);
        printf("Current node : (%d;%d)\n", current_node.i, current_node.j);
        current_node.open = 2;
        for (int a = -1; a <= 1; a++)
        {
            for (int b = -1; b <= 1; b++)
            {
                if (a == 0 && b == 0)
                {
                    //printf("CONDITION ATTEINTE\n");
                    //continue;
                }
                
                if (current_node.i + a >= 0 && current_node.j + b >= 0 
                    && current_node.i + a < m->width
                    && current_node.j + b < m->width 
                    && current_node.i + a < m->height
                    && current_node.j + b < m->height) 
                {
                    printf("Current node : %d;%d\n", current_node.i, current_node.j);
                    map[current_node.i + a][current_node.j + b].type = 'V';
                    //if (temp.type == '#' || temp.open == 1)
                    //{
                        //continue;
                    //}       
                    
                }
            }
        }
        if (current_node.j + 1 < m->width)
        {
        current_node = map[current_node.i][current_node.j + 1];
        }
        else
        {
            break;
        }
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
    map = nodes;
    find_shortest_path(start, finish, m);

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c",nodes[i][j].type);
        }
        fprintf(stdout,"\n");
    }

    return nodes;
}
