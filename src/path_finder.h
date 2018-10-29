#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "control.h"

struct node
{
    char type;
    char open; /* 0 -> not seen | 1 -> closed | 2 -> open */
    struct node *next; /* Position in matrix of following node*/
    struct node *previous; /* Position in matrix of previous node*/
    struct vector2 pos; /* Position on the map*/
    float f_cost;
    int i; /* Indexes in the matrix */ 
    int j;
};

struct node **map_init(struct map *map);

void destroy_map(void);

struct node **g_map;

#endif /* PATH_FINDER_H */
