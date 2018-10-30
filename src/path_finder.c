#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "control.h"
#include "path_finder.h"
#include "utilities.h"

static struct node *find_neighbors(struct node *node, int *size, struct map *m,
    struct node *finish)
{
    struct node *neighbors = malloc(sizeof(neighbors) * 8);

    for (int a = -1; a <= 1; a++)
    {
        for (int b = -1; b <= 1; b++)
        {
            // TODO take diagonals into account, when possible 
            if (abs(a) == abs(b))
            {
                continue;
            }

            if (node->i + a >= 0 && node->j + b >= 0
                    && node->i + a < m->width
                    && node->j + b < m->width)
            {
                printf("i :  %d | j = %d\n", node->i +a, node->j + b);
                neighbors[*size] = g_map[node->i + a][node->j + b];
                g_map[node->i + a][node->j + b].open = 1;


                float g_cost = get_cost_vector(neighbors[*size].pos, node->pos) + node->g_cost;
                float h_cost = get_cost_vector(finish->pos, neighbors[*size].pos);

                neighbors[*size].f_cost = g_cost + h_cost;
                neighbors[*size].g_cost = g_cost;
                neighbors[*size].h_cost = h_cost;

                *size++;
            }
        }
    }
}

void find_shortest_path(struct node *start, struct node *finish, struct map *m)
{
    struct list_node *list_open = init_list(start);
    while (1)
    {
        struct node *current_node = pop_list(list_open)->node;
        current_node->open = 2;

        if (vector_cmp(current_node->pos, finish->pos))
        {
            break;
        }
        int size = 0;
        struct node *neighbors = find_neighbors(current_node, &size, m, finish);

        for (int i = 0; i < size; i++)
        {
            if (neighbors[i].type == '#' ||
                    neighbors[i].type == '"' ||
                    neighbors[i].open == 2)
            {
                continue;
            }

            float new_path = neighbors[i].f_cost;
            float current_path = current_node->f_cost;

            if (new_path < current_path || !find_element(list_open, &neighbors[i]))
            {
                //neighbors[i].f_cost = get_cost_vector();
                neighbors[i].previous = current_node;
                if (!find_element(list_open, &neighbors[i]))
                {
                    list_open = insert(list_open, &neighbors[i]);
                }
            }

        }
    }
}

struct node **map_init(struct map *m)
{
    int mwidth = m->width;
    int mheight = m->height;

    printf("width of the map %d \n", mwidth);
    printf("height of the map %d \n", mheight);
    printf("x start %f \n", m->start.x);
    printf("y start %f \n", m->start.y);

    struct node start;

    struct node finish;

    struct node **nodes = malloc(sizeof(void *) * mheight);


    for (int i = 0; i < mheight; i++)
    {
        nodes[i] = malloc(sizeof(struct node) * mwidth);
        for (int j = 0; j < mwidth; j++)
        {
            nodes[i][j].open = 0;
            nodes[i][j].pos.x = j + 0.5;
            nodes[i][j].pos.y = i + 0.5;
            nodes[i][j].i = i;
            nodes[i][j].j = j;
            if (map_get_floor(m, j, i) == FINISH)
            {
                nodes[i][j].type = 'F';
                finish = nodes[i][j];
            }
            else if (j == floor(m->start.x) && i == floor(m->start.y))
            {
                nodes[i][j].type = 'S';
                start = nodes[i][j];
            }
            else if (map_get_floor(m, j, i) == BLOCK)
            {
                nodes[i][j].type = '#';
            }
            else if (map_get_floor(m, j, i) == GRASS)
            {
                nodes[i][j].type = '"';
            }
            else
            {
                nodes[i][j].type = (map_get_floor(m, j, i) == ROAD) + '0';
            }
        }
    }
    g_map = nodes;

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c",nodes[i][j].type);
        }
        fprintf(stdout,"\n");
    }

    find_shortest_path(&start, &finish, m);
    puts("DISPLAYING SHORTEST PATH:");

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            fprintf(stdout," %c", g_map[i][j].type);
        }
        fprintf(stdout,"\n");
    }
    return nodes;
}
