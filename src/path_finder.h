#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "control.h"

struct node
{
    char type;
    char open; /* 0 -> not seen | 1 -> open | 2 -> closed */
    struct node *next; /* Position in matrix of following node*/
    struct node *previous; /* Position in matrix of previous node*/
    struct vector2 pos; /* Position on the map*/
    float f_cost;
    float h_cost;
    float g_cost;
    int i; /* Indexes in the matrix */ 
    int j;
};

struct node **map_init(struct map *map);

void destroy_map(int size);

struct node **g_map;

/* TODO: REMOVE GLOBAL VARIABLE, use static variable in update function*/

#endif /* PATH_FINDER_H */
