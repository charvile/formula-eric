#include "utilities.h"
#include <math.h>
#include <stdio.h>

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

int cmp_vec(struct vector2 v1, struct vector2 v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

float get_abs_angle_2_pts(struct vector2 P1, struct vector2 P2)
{

    if (cmp_vec(P1, P2))
    {
        //puts("The two points are equal");
        return 0;
    }
    struct vector2 V12;
    struct vector2 X01 = {1,0};

    /* we define the 2 vectors made by the 3 points */
    V12.x = P2.x - P1.x;
    V12.y = P2.y - P1.y;
    /* we compute the scalar product 2 ways to use the cosine of the 2 vectors */
    float product = scalar_product(X01, V12);

    float len_V12 = sqrt(pow(V12.x, 2) + pow(V12.y, 2));
    float len_X01 = sqrt(pow(X01.x, 2) + pow(X01.y, 2));

    /* result given in radians by acos */
    float res = acos(product/(len_V12 * len_X01));

    if (V12.y < 0)
    {
        res = 2 *  M_PI - res;
    }

    return res;
}

float det(struct vector2 V1, struct vector2 V2)
{
	return V1.x * V2.y - V1.y * V2.x;
}

struct vector2 make_vector(struct vector2 P1, struct vector2 P2)
{
	struct vector2 vec;
	vec.x = P2.x - P1.y;
	vec.y = P2.y - P1.y;
	return vec;
}


float get_angle_3_pts(struct vector2 P1, struct vector2 P2, struct vector2 P3)
{

    if (cmp_vec(P1, P2) || cmp_vec(P2, P3) || cmp_vec(P1, P3))
    {
        //puts("Two point are equal");
        return 0;
    }
    struct vector2 V12;
    struct vector2 V23;

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
    //printf("Res is %f\n", res);

    return res;
}


