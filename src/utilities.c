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

float scalar_product(struct vector2 V1, struct vector2 V2)
{
	float ret;
	ret = V1.x * V2.x + V1.y * V2.y;

	return ret;
}

float get_angle_3_pts(struct vector2 P1, struct vector2 P2, struct vector2 P3)
{
	float vector2 V12;
	float vector2 V23;
	
	/* we define the 2 vectors made by the 3 points */
	V12.x = P2.x - P1.x;
	V12.y = P2.y - P1.y;
	V23.x = P3.x - P2.x;
	V23.y = P3.y - P2.y;

	/* we compute the scalar product 2 ways to use the cosine of the 2 vectors */
	float product = scalar_product(V12, V23);

	float len_V12 = sqrt(pow(V12.x, 2) + pow(V12.y, 2));
	float len_V23 = sqrt(pow(V23.x, 2) + pow(V23.y, 2));
	
	/* result given in radians by acos */
	float res = acos(product/(len_V12 * len_V23));

	return res;
}
