#ifndef PATH_FINDER_H
#define PATH_FINDER_H

struct node
{
    char value;
    struct node neighbor[8];
    struct vector2 pos;
};







#endif /* PATH_FINDER_H */
