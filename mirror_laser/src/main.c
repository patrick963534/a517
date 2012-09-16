#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sl_list.h"

#define DIR_L   1
#define DIR_R   2
#define DIR_U   3
#define DIR_D   4

#define G_NORMAL         0x1000
#define G_BLOCK_NORMAL   0x4000

#define M_LASER_L        0x0100
#define M_LASER_R        0x0200
#define M_LASER_U        0x0300
#define M_LASER_D        0x0400
#define M_MIRROR_LD      0x0500
#define M_MIRROR_LU      0x0600

static int map_data[] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1200, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1500, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1600, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
};

static int map_width  = 12;
static int map_height = 10;

static int *map;

static void print_map()
{
    int i, j;

    for (j = 0; j < map_height; j++)
    {
        for (i = 0; i < map_width; i++)
        {
            printf("%04x, ", map[i + j * map_width]);
        }

        printf("\n");
    }
}

typedef struct light_t
{
    sl_list_t   e;
    int         x;
    int         y;
    int         dir;
} light_t;

typedef struct laser_t
{
    sl_list_t   e;
    sl_list_t   lights;

    int         x;
    int         y;
    int         type;
} laser_t;

static sl_list_t lasers;

static void update_pos(int *x, int *y, int dir)
{
    switch (dir)
    {
        case DIR_L: *x = *x - 1; break;
        case DIR_R: *x = *x + 1; break;
        case DIR_U: *y = *y - 1; break;
        case DIR_D: *y = *y + 1; break;
        default: break;
    }
}

static void update_dir(int ground, int* dir)
{
    if ((ground & 0x0F00) == M_MIRROR_LD)
    {
        switch (*dir)
        {
            case DIR_L: *dir = DIR_U; break;
            case DIR_R: *dir = DIR_D; break;
            case DIR_U: *dir = DIR_L; break;
            case DIR_D: *dir = DIR_R; break;
            default: assert(!"unknow direction of light.");
        }
    }
    else if ((ground & 0x0F00) == M_MIRROR_LU)
    {
        switch (*dir)
        {
            case DIR_L: *dir = DIR_D; break;
            case DIR_R: *dir = DIR_U; break;
            case DIR_U: *dir = DIR_R; break;
            case DIR_D: *dir = DIR_L; break;
            default: assert(!"unknow direction of light.");
        }
    }
}

static void create_laser(int x, int y, int type)
{
    laser_t *me;
    int dir;
    int count;
    
    me = malloc(sizeof(*me));
    me->x = x;
    me->y = y;
    me->type = type;

    sl_list_init(&me->e);
    sl_list_init(&me->lights);

    dir = type >> 8;
    count = 0;

    printf("\n**********begin lights**********\n");

    while (1)
    {
        int ground;
        light_t *l;

        if (count++ > 10000)
            assert(!"failure to generate lights for laser.");


        update_pos(&x, &y, dir);
        ground = map[x + y * map_width];
        
        if (x < 0 || y < 0 || x >= map_width || y >= map_height)
            break;

        if ((ground & 0xF000) != G_NORMAL)
            break;

        l = malloc(sizeof(*l));
        l->x = x;
        l->y = y;
        l->dir = dir;
        sl_list_init(&l->e);
        sl_list_add_tail(&me->lights, &l->e);

        printf("(%02d,%02d) ", x, y);

        update_dir(ground, &dir);
    }

    printf("\n");
}

static void generate_lasers()
{
    int i, j;

    sl_list_init(&lasers);

    for (j = 0; j < map_height; j++)
    {
        for (i = 0; i < map_width; i++)
        {
            int type = map[i + j * map_width] & 0x0F00;
            switch (type)
            {
                case M_LASER_L:
                case M_LASER_R:
                case M_LASER_U:
                case M_LASER_D:
                    create_laser(i, j, type);
                    break;
                default:
                    break;
            }
        }
    }
}

int main()
{ 
    map = map_data;

    print_map();
    generate_lasers();

    return 0;
}
