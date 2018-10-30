#include "path_finder.h"
#include <stdlib.h>
#include <stdio.h>


struct list_node *init_list(struct node *node)
{
    if (!node)
    {
        return NULL;
    }
    struct list_node *ret = malloc(sizeof(struct list_node));
    struct list_element *elt = malloc(sizeof(struct list_element));
    ret->size = 1;
    ret->first = elt;
    elt->node = node;
    elt->next = NULL;
    return ret;
}

struct list_node *insert(struct list_node *list, struct node *node)
{
    if (!list || !node)
    {
        return NULL;
    }
    struct list_element *elt = malloc(sizeof(struct list_element));
    list->size++;
    elt->node = node;
    if (!list->first)
    {
        list->first = elt;
        elt->next = NULL;
        return list;
    }
    elt->next = list->first;
    list->first = elt;
    return list;
}

struct list_node *remove_list(struct list_node *list, struct node *node)
{
    if (!list || !node)
    {
        return NULL;
    }
    if (!list->first)
    {
        return NULL;
    }
    struct list_element *temp = list->first;
    struct list_element *temp2 = NULL;
    if (temp->node == node)
    {
        list->first = temp->next;
        free(temp);
        return list;
    }
    temp2 = temp;
    temp = temp->next;
    while (temp)
    {
        if (temp->node == node)
        {
            temp2->next = temp->next;
            free(temp);
            return list;
        }
        temp2 = temp;
        temp = temp->next;
    }
    fprintf(stderr,"Did not find the node.");
    return list;
}

void destroy(struct list_node *list)
{
    if (!list)
    {
        return;
    }
    if (!list->first)
    {
        free(list);
        return;
    }
    struct list_element *temp = list->first;
    struct list_element *temp2 = temp;
    while (temp->next)
    {
        temp = temp->next;
        free(temp2);
        temp2 = temp;
    }
    free(list);
}

struct list_element *pop_list(struct list_node *list)
{
    if (!list)
    {
        return NULL;
    }
    if (!list->first)
    {
        return NULL;
    }
    struct list_element *elt = list->first;
    if (!elt->next)
    {
        return elt;
    }
    float f_cost = elt->node->f_cost;
    float h_cost = elt->node->h_cost;
    struct list_element *min_elt = elt;
    float min_f = f_cost;;
    float min_h = h_cost;;
    struct list_element *ret = elt;
    elt = elt->next;
    while (elt)
    {
        if (elt->node->f_cost < min_f)
        {
            min_f = elt->node->f_cost;
            min_elt = elt;
            min_h = elt->node->h_cost;
        }
        else if (elt->node->f_cost == min_f)
        {
            if (elt->node->h_cost < min_h)
            {
                min_h = elt->node->h_cost;
                min_elt = elt;
            }
        }
        ret = elt;
        elt = elt->next;
    }
    return ret;
}


struct list_element *find_element(struct list_node *list, struct node *node);
