#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "control.h"
#include <stddef.h>

struct list_element
{
    struct node *node;
    struct list_element *next;
};

struct list_node
{
    size_t size;
    struct list_element *first;
};

/* NOTE: list functions*/

struct list_node *init_list(struct node *node);
struct list_node *insert(struct list_node *list, struct node *node);
struct list_node *remove_list(struct list_node *list, struct node *node);
void destroy(struct list_node *list);
struct list_element *pop_list(struct list_node *list);
struct list_element *find_element(struct list_node *list, struct node *node);



struct node
{
    char type;
    char open; /* 0 -> not seen | 1 -> open | 2 -> closed */
    struct node *previous; /* Position in matrix of previous node*/
    struct vector2 pos; /* Position on the map*/
    float f_cost;
    float h_cost;
    float g_cost;
    int i; /* Indexes in the matrix */
    int j;
};

struct node **map_init(struct map *map);
struct node *find_neighbors(struct node *node, int *size, struct map *m,struct node *finish);

void destroy_map(int size);
void find_shortest_path(struct node *start, struct node *finish, struct map *m);

void draw_best_path(struct node *start, struct node *finish);
struct node **g_map;

/* TODO: REMOVE GLOBAL VARIABLE, use static variable in update function*/

#endif /* PATH_FINDER_H */
