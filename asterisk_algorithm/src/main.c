#include <stdio.h>
#include <stdlib.h>
#include "sl_list.h"

/*
    ground_normal:          0x1000
    ground_ice:             0x2000
    ground_fire:            0x3000
    ground_ice_triple:      0x4000
    ground_normal_triple:   0x5000
    ground_start:           0x6000
    ground_end:             0x7000

    machine_laser_u:        0x0100
    machine_laser_d:        0x0200
    machine_laser_l:        0x0300
    machine_laser_r:        0x0400
    machine_mirror_l:       0x0500
    machine_mirror_r:       0x0600
    machine_bomb:           0x0700
    machine_fan_u:          0x0800
    machine_fan_d:          0x0900
    machine_fan_l:          0x0A00
    machine_fan_r:          0x0B00

    tool_laser_u:           0x0001
    tool_laser_d:           0x0002
    tool_laser_l:           0x0003
    tool_laser_r:           0x0004
    tool_mirror_l:          0x0005
    tool_mirror_r:          0x0006
    tool_bomb:              0x0007
    tool_fan_u:             0x0008
    tool_fan_d:             0x0009
    tool_fan_l:             0x000A
    tool_fan_r:             0x000B
    tool_bucket:            0x000C
    tool_fire:              0x000D
*/

typedef struct node_t
{
    sl_list_t   e;
    int         f;  /* distance from this node to end.  */
    int         g;  /* distance from start to this node.  */
    int         h;  /* distance from parent to this node. */
    int         x;
    int         y;

    struct node_t*  p;  /* parent */
} node_t;

static int map_data[] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
};

static int map_width  = 12;
static int map_height = 10;

static sl_list_t open;
static sl_list_t close;

static void print_map()
{
    int *map = map_data;
    int i, j;

    for (j = 0; j < map_height; j++)
    {
        for (i = 0; i < map_width; i++)
        {
            printf("%04x, ", map[i + j * map_height]);
        }

        printf("\n");
    }
}

static void print_path()
{
    
}

static node_t* create_node(int x, int y, int dx, int dy, node_t* p)
{
    node_t* me = calloc(1, sizeof(*me));
    me->x = x;
    me->y = y;
    me->p = p;

    me->h = 0;
    me->g = 0;
    me->f = (abs(me->x - dx) + abs(me->y - dy)) * 10;

    if (p)
    {
        me->h = (p->x == x || p->y == y) ? 10 : 14;
        me->g = p->g + me->h;
    }

    sl_list_init(&me->e);

    return me;
}

static const node_t* contains(sl_list_t* head, int x, int y)
{
    node_t *p;

    sl_list_for_each_entry(p, head, node_t, e)
    {
        if (p->x == x && p->y == y)
            return p;
    }

    return NULL;
}

static void add_neighbor_node(node_t* cur, int dx, int dy)
{
    node_t *p;
    int i, j;

    for (j = -1; j < 2; j++)
    {
        for (i = -1; i < 2; i++)
        {
            int x = cur->x + i;
            int y = cur->y + j;

            if (contains(&open, x, y) || contains(&close, x, y))
                continue;

            p = create_node(x, y, dx, dy, cur);
            sl_list_add_tail(&open, &p->e);
        }
    }
}

static void search(int sx, int sy, int dx, int dy)
{
    node_t *p;
    int count = 0;

    printf("\n***************start path searching***************\n");

    sl_list_init(&open);
    sl_list_init(&close);
    
    p = create_node(sx, sy, dx, dy, NULL);   
    sl_list_add_tail(&open, &p->e);

    while (!sl_list_empty(&open))
    {
        p = sl_list_first_entry(&open, node_t, e);

        printf("(%02d,%02d) ", p->x, p->y);
        if (++count % map_width == 0)
            printf("\n");

        add_neighbor_node(p, dx, dy);

        if (p->x == dx && p->y == dy)
            break;
        
        sl_list_remove(&p->e);
        sl_list_add_tail(&close, &p->e);
    }

    printf("\n***************finish path searching**************\n");
}

int main()
{
    print_map();
    search(5, 5, 8, 10);
    print_path();

    return 0;
}
