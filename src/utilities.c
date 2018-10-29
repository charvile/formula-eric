#include "utilities.h"
#include <math.h>

float get_distance(float x1, float x2, float y1, float y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

float get_angle(float x1, float x2, float y1, float y2)
{
    float slope = (y2 - y1) / (x2 - x1);
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

int vector_cmp(struct vector2 v1, struct vector2 v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

struct node find_minimum(struct node *neighbors, int size)
{
    float min = neighbors[0].f_cost;
    int min_index = 0;
    for (int i = 1; i < size; i++)
    {
        if (neighbors[i].f_cost < min)
        {
            min_index = i;
            min = neighbors[i].f_cost;
        }
    }
    return neighbors[min_index];
}
