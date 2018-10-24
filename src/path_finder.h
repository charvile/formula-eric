#ifndef PATH_FINDER_H
#define PATH_FINDER_H

struct node
{
    char type;
    struct vector2 next;
};

struct node **map_init(struct map *map);

struct node **map;



#endif /* PATH_FINDER_H */
