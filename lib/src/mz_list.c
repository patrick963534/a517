#include <mz/mz_list.h>
#include <mz/mz_general_list.h>
#include <mz/mz_libs.h>

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
    mz_general_list_t *pos;

    mz_general_list_for_each(pos, &me->head) {
        if (pos == &v->node) 
            return i;
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
    mz_general_list_t *pos;

    mz_general_list_for_each(pos, &me->head) {
        if (i == index) 
            break;
        i++;
    }

    if (pos == &me->head)
        return NULL;

    return mz_list_entry(pos, mz_list_item_t);
}

MZ_API void mz_list_delete(mz_list_t *me)
{
    mz_list_clear(me);
    mz_free(me);
}

MZ_API void mz_list_clear(mz_list_t *me)
{
    mz_list_item_t *pos, *next_pos;
        
    mz_list_for_each_entry_safe(pos, next_pos, me, mz_list_item_t) {
        mz_list_remove(me, pos);
    }
}

MZ_API void mz_list_each_do(mz_list_t *me, mz_list_do_func func)
{
    mz_list_item_t *pos, *next_pos;
        
    mz_list_for_each_entry_safe(pos, next_pos, me, mz_list_item_t) {
        func(pos->ptr_ref);
    }
}
