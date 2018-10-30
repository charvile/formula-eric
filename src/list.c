#include "path_finder.h"

struct list_node *init_list(struct node *node);
struct list_node *insert(struct list_node *list, struct node *node);
struct list_node *remove(struct list_node *list, struct node *node);
void destroy(struct list_node *list);
struct list_element *pop_list(struct list_node *list);
struct list_element *find_element(struct list_node *list, struct node *node);

