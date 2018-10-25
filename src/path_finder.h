#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "contol.h"

struct node
{
    char type;
    char open; /* 0 -> not seen | 1 -> closed | 2 -> open */
    struct vector2 next; /* Position in matrix of following node*/
    struct vector2 previous; /* Position in matrix of previous node*/
    struct vector2 pos; /* Position on the map*/
    int i; /* Indexes in the matrix */ 
    int j;
};

struct node **map_init(struct map *map);

struct node **g_map;

#endif /* PATH_FINDER_H */
