#include <mz/mz_list.h>
#include <mz/mz_general_list.h>
#include <mz/mz_libs.h>

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

MZ_API int mz_list_position(mz_list_t *me, mz_list_item_t *v)
{
    int i = 0;

    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        if (me->pos == v)
            return i;

        mz_list_iterator_next(me);
        i++;
    }
    
    return -1;
}

MZ_API void mz_list_remove(mz_list_t *me, mz_list_item_t *v)
{
    mz_general_list_remove(&v->node);
    me->count--;

    mz_free(v);
}

MZ_API mz_list_item_t* mz_list_index(mz_list_t *me, int index)
{
    int i = 0;

    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        if (i == index)
            return me->pos;

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
    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        mz_list_remove(me, me->pos);
        mz_list_iterator_next(me);
    }
}

MZ_API void mz_list_each_do(mz_list_t *me, mz_list_do_func func)
{
    mz_list_iterator_begin(me);
    while (!mz_list_iterator_eof(me)) {
        func(me->pos->ptr_ref);
        mz_list_iterator_next(me);
    }
}

MZ_API mz_bool mz_list_iterator_eof(mz_list_t *me)
{
    return &me->pos->node == &me->head;
}

MZ_API void mz_list_iterator_begin(mz_list_t *me)
{
    me->pos = mz_list_entry(me->head.next, mz_list_item_t);
    me->bak_pos = mz_list_entry(me->pos->node.next, mz_list_item_t);
}

MZ_API void mz_list_iterator_next(mz_list_t *me)
{
    me->pos = me->bak_pos;
    me->bak_pos = mz_list_entry(me->pos->node.next, mz_list_item_t);
}
