#include <mz/mz_queue.h>

MZ_API mz_queue_t* mz_queue_new()
{
    mz_queue_t  *me;
    me = mz_malloc(sizeof(*me));
    me->root = mz_list_new();

    return me;
}

MZ_API void mz_queue_delete(mz_queue_t *me)
{
    mz_queue_clear(me);
    mz_list_delete(me->root);
    mz_free(me);
}

MZ_API void mz_queue_push(mz_queue_t *me, void *value)
{
    mz_list_add(me->root, value);
}

MZ_API void* mz_queue_pop(mz_queue_t *me)
{
    void *v = mz_list_get_first(me->root);

    mz_list_remove_first(me->root);

    return v;
}

MZ_API void mz_queue_clear(mz_queue_t *me)
{
    mz_list_clear(me->root);
}
