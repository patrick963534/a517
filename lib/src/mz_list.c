#include <mz/mz_list.h>
#include <mz/mz_general_list.h>
#include <mz/mz_libs.h>

typedef struct mz_list_item_t
{
    mz_general_list_t   node;
    void                *ptr_ref;
} mz_list_item_t;

#define mz_list_entry(ptr, type) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->node)))

MZ_API mz_list_t* mz_list_new()
{
    mz_list_t *me = mz_malloc(sizeof(*me));

    mz_general_list_init(&me->head);

    return me;
}

MZ_API void mz_list_add(mz_list_t *me, void *v)
{
    mz_list_item_t *it;

    it = (mz_list_item_t*)mz_malloc(sizeof(*it));
    mz_general_list_init(&it->node);
    mz_general_list_add(&it->node, &me->head);
    me->count++;

    it->ptr_ref = v;
}

MZ_API int mz_list_position(mz_list_t *me, void *v)
{
    int i = 0;

    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        if (mz_list_iterator_current(me) == v)
            return i;

        mz_list_iterator_next(me);
        i++;
    }
    
    return -1;
}

MZ_API void mz_list_remove(mz_list_t *me, void *v)
{
    mz_list_item_t *it;
    
    mz_list_iterator_begin(me);

    while (!mz_list_iterator_eof(me)) {
        if (mz_list_iterator_current(me) == v) {
            it = mz_list_entry(me->pos, mz_list_item_t);
            mz_general_list_remove(me->pos);
            mz_free(it);
            me->count--;
            return;
        }

        mz_list_iterator_next(me);
    }

    logI("Can't find object to delete.");
    mz_assert(0);
}

MZ_API void* mz_list_index(mz_list_t *me, int index)
{
    int i = 0;

    if (index >= me->count) {
        logI("index '%d' should less than count '%d'.", index, me->count);
        mz_assert(0);
    }

    mz_list_iterator_begin(me);

    while (!mz_list_iterator_eof(me)) {
        if (i == index)
            return mz_list_iterator_current(me);

        mz_list_iterator_next(me);
        i++;
    }

    return NULL;
}

MZ_API void mz_list_delete(mz_list_t *me)
{
    mz_list_clear(me);
    mz_free(me);
}

MZ_API void mz_list_clear(mz_list_t *me)
{
    mz_list_item_t *it;
    mz_list_iterator_begin(me);

    while (!mz_list_iterator_eof(me)) {
        it = mz_list_entry(me->pos, mz_list_item_t);
        mz_general_list_remove(me->pos);
        mz_free(it);
        mz_list_iterator_next(me);
        me->count--;
    }
}

MZ_API void mz_list_each_do(mz_list_t *me, mz_list_do_func func)
{
    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        func(mz_list_iterator_current(me));
        mz_list_iterator_next(me);
    }
}

MZ_API mz_bool mz_list_iterator_eof(mz_list_t *me)
{
    return me->pos == &me->head;
}

MZ_API void mz_list_iterator_begin(mz_list_t *me)
{
    me->pos = me->head.next;
    me->bak_pos = me->pos->next;
}

MZ_API void mz_list_iterator_next(mz_list_t *me)
{
    me->pos = me->bak_pos;
    me->bak_pos = me->pos->next;
}

MZ_API void* mz_list_iterator_current(mz_list_t *me)
{
    mz_list_item_t *it;
    it = mz_list_entry(me->pos, mz_list_item_t);
    return it->ptr_ref;
}
