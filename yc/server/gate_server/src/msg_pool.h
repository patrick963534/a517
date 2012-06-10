#ifndef __MSG_POOL_H__
#define __MSG_POOL_H__

#include <mz/mz_list.h>
#include <mz/mz_thread.h>
#include <mz/mz_libs.h>
#include <mz/mz_rudp.h>

typedef struct yc_msg_pool_item_t
{
    char                *data;
    int                 ndata;

    mz_rudp_addr_t      from_addr;
    mz_rudp_t           *rudp;
} yc_msg_pool_item_t;

typedef struct yc_msg_pool_t
{
    mz_list_t           *queue;
    mz_thread_mutex_t   *mutex;
} yc_msg_pool_t;

yc_msg_pool_item_t* yc_msg_pool_item_new(const char *data, int len);
void                yc_msg_pool_item_delete(yc_msg_pool_item_t* me);

yc_msg_pool_t*      yc_msg_pool_new();
int                 yc_msg_pool_count(yc_msg_pool_t *me);
void                yc_msg_pool_end_queue(yc_msg_pool_t *me, yc_msg_pool_item_t *item);
yc_msg_pool_item_t* yc_msg_pool_pop(yc_msg_pool_t *me);
void                yc_msg_pool_delete(yc_msg_pool_t* me);


yc_msg_pool_t* yc_msg_pool_new()
{
    yc_msg_pool_t *me = mz_malloc(sizeof(*me));
    me->queue = mz_list_new_ptr_ref();
    me->mutex = mz_thread_mutex_new();

    return me;
}

void yc_msg_pool_end_queue(yc_msg_pool_t *me, yc_msg_pool_item_t *item)
{
    mz_thread_mutex_lock(me->mutex);

    mz_list_add_ptr_ref(me->queue, item);

    mz_thread_mutex_unlock(me->mutex);
}

yc_msg_pool_item_t* yc_msg_pool_pop(yc_msg_pool_t *me)
{
    yc_msg_pool_item_t *item = NULL;
    mz_list_item_t *first;

    mz_thread_mutex_lock(me->mutex);

    first = mz_list_index(me->queue, 0);
    if (first != NULL) {
        item = (yc_msg_pool_item_t*)((mz_list_item_ptr_ref_t*)first)->ptr_ref;
        mz_list_remove(me->queue, first);
    }
    
    mz_thread_mutex_unlock(me->mutex);

    return item;
}

void yc_msg_pool_delete(yc_msg_pool_t* me)
{
    mz_list_delete(me->queue);
    mz_thread_mutex_delete(me->mutex);
    mz_free(me);
}

yc_msg_pool_item_t* yc_msg_pool_item_new(const char *data, int len)
{
    yc_msg_pool_item_t *me = mz_malloc(sizeof(*me));
    me->data = mz_malloc(len);
    me->ndata = len;
    mz_memcpy(me->data, data, len);

    return me;
}

void yc_msg_pool_item_delete(yc_msg_pool_item_t *me)
{
    mz_free(me->data);
    mz_free(me);
}

int yc_msg_pool_count(yc_msg_pool_t *me)
{
    return me->queue->count;
}

#endif
