#include "path_finder.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void draw_best_path(struct node *start, struct node *finish)
{
    struct node *current = finish;

    //printf("Currently on %d;%d\n", current->i, current->j);
    while(!vector_cmp(current->pos, start->pos))
    {
        //printf("Previous is %d;%d\n", current->previous->i, current->previous->j);
        current = &g_map[current->previous->i][current->previous->j];
        g_map[current->i][current->j].type = '@';
    }
}

void set_checkpoints(struct node *start, struct node *finish)
{
    struct node *current = finish;
    struct node *next = current;

    float current_angle = 0;
    int count = 0;
    while(!vector_cmp(current->pos, start->pos))
    {
        if (count == 0)
        {
            current_angle = get_angle_vector(current->pos,
                    current->previous->pos);
        }

        float angle = get_angle_vector(current->previous->pos, current->pos);
        //printf("Angle is %.3f\n", angle);

        if (angle != current_angle)
        {
            g_map[current->i][current->j].type = 'C';
            current_angle = angle;
            next = current;
        }
        g_map[current->i][current->j].next_checkpoint = next;
        count++;
        current = current->previous;
    }
    g_map[start->i][start->j].next_checkpoint = next;
}

void destroy_map(int size)
{
    for (int i = 0; i < size; i++)
    {
        free(g_map[i]);
    }

    free(g_map);
}

int is_valid_diagonal(struct node *node, int a, int b)
{
    if (abs(a) == abs(b) && (g_map[node->i + a][node->j].type == '#' &&
        g_map[node->i][node->j + b].type == '#'))
    {
        return 0;
    }
    return 1;
}

struct node *find_neighbors(struct node *node, int *size, struct map *m,
        struct node *finish)
{
    //printf("Map height = %d\nMap width = %d\n", m->height, m->width);
    struct node *neighbors = malloc(sizeof(*neighbors) * 8);

    if (!neighbors)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }


    for (int a = -1; a <= 1; a++)
    {
        for (int b = -1; b <= 1; b++)
        {
            // TODO take diagonals into account, when possible
            if (a == 0 && b == 0)
            {
                continue;
            }
            if (node->i + a >= 0 && node->j + b >= 0
                    && node->i + a < m->height
                    && node->j + b < m->width
                    && is_valid_diagonal(node, a, b))
                //      )
            {
                neighbors[*size] = g_map[node->i + a][node->j + b];
                //g_map[node->i + a][node->j + b].open = 1;

                float g_cost = get_cost_vector(neighbors[*size].pos, node->pos) + node->g_cost;
                float h_cost = get_cost_vector(finish->pos, neighbors[*size].pos);

                neighbors[*size].f_cost = g_cost + h_cost;
                neighbors[*size].g_cost = g_cost;
                neighbors[*size].h_cost = h_cost;

                *size += 1;
            }
        }
    }

    return neighbors;
}
