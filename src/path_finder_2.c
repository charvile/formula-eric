#include "path_finder.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void draw_best_path(struct node start, struct node finish)
{
    struct node current = finish;

    while(current.pos.x != start.pos.x && current.pos.y != start.pos.y)
    {
        current = g_map[current.previous->i][current.previous->j]; 
        g_map[current.i][current.j].type = '-';
    }
}

void set_checkpoints(struct node start, struct node finish);
/*{
  struct node current = start;

  float current_angle = 0;
  int count = 0;
  while(!vector_cmp(current.pos, finish.pos))
  {
  if (count == 0)
  {
  current_angle = get_angle_vector(current.pos, 
  current.previous->pos);
  }

  float angle = get_angle_vector(current.pos, current.next->pos);

  if (angle != current_angle)
  {
  current.type = 'C';
  current_angle = angle;
  }
  count++;
  }
  }*/

void destroy_map(int size)
{
    for (int i = 0; i < size; i++)
    {
        free(g_map[i]);
    }

    free(g_map);
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
            if (abs(a) == abs(b))
            {
                continue;
            }
            if (node->i + a >= 0 && node->j + b >= 0
                    && node->i + a < m->height
                    && node->j + b < m->width)
                //      )
            {
                neighbors[*size] = g_map[node->i + a][node->j + b];
                g_map[node->i + a][node->j + b].open = 1;

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
