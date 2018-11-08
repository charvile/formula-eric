#include "control.h"
#include <math.h>
#include "path_finder.h"
#include "steering.h"
#include <stdio.h>
#include <stdlib.h>

#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"
#define RESET "\x1B[0m"

struct node **map_init(struct map *m)
{
    int mwidth = m->width;
    int mheight = m->height;

    struct node *start;

    struct node *finish;

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
            nodes[i][j].next_checkpoint = NULL;
            if (map_get_floor(m, j, i) == FINISH)
            {
                nodes[i][j].type = 'F';
                finish = &nodes[i][j];
            }
            else if (j == floor(m->start.x) && i == floor(m->start.y))
            {
                nodes[i][j].type = 'S';
                start = &nodes[i][j];
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
                nodes[i][j].type = ' ';//(map_get_floor(m, j, i) == ROAD) + '0';
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

    find_shortest_path(start, finish, m);
    draw_best_path(start, finish);
    set_checkpoints(start, finish);
    puts("DISPLAYING SHORTEST PATH:");

    for (int i = 0; i < mheight; i++)
    {
        for (int j = 0; j < mwidth; j++)
        {
            if (g_map[i][j].type == '@' || g_map[i][j].type == 'C')
            {
                fprintf(stdout, "%s %c%s", KBLU, g_map[i][j].type, RESET);
            }
            else if (g_map[i][j].type == '#')
            {
                fprintf(stdout, "%s %c%s", KRED, g_map[i][j].type, RESET);
            }
            else if (g_map[i][j].type == '"')
            {
                fprintf(stdout, "%s %c%s", KGRN, g_map[i][j].type, RESET);
            }
            else
            {
                fprintf(stdout," %c", g_map[i][j].type);
            }
        }
        fprintf(stdout,"\n");
    }
    puts("DISPLAYING CHECKPOINTS");
    //struct node *temp = &g_map[start->i][start->j];
    //while(temp && (temp->i != finish->j && temp->i != finish->j))
    //{
        //printf("Checkpoint : %d;%d\n", temp->i, temp->j);
        //temp = &g_map[temp->next_checkpoint->i][temp->next_checkpoint->j];
    //}

    puts("DONE");
    return nodes;
}

enum move update(struct car *car)
{
    if (!g_map)

    {
        map_init(car->map);
    }
    return get_next_action(car);
}
