#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "path_finder.h"


struct node **map_init(struct map *map)
{
    int mwidth = map->width;
    int mheight = map->height;

    printf("width of the map %d \n", mwidth);
    printf("height of the map %d \n", mheight);
    printf("x start %f \n", map->start.x);
    printf("y start %f \n", map->start.y);

    struct node **nodes = malloc(sizeof(void *) * mheight);
    
    
    for (int i = 0; i < mheight; i++)
    {
        nodes[i] = malloc(sizeof(struct node) * mwidth);
        for (int j = 0; j < mwidth; j++)
        {
            nodes[i][j].type = (map_get_floor(map, j, i) == ROAD);
        }
    }
    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
           fprintf(stdout," %d",nodes[i][j].type);
        }
        fprintf(stdout,"\n");
    }
    return nodes;
}


