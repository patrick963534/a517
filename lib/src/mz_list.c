#include <mz/mz_list.h>
#include <mz/libs/mz_memory.h>
#include <mz/libs/mz_defs.h>

MZ_API mz_list_t* mz_list_new()
{
    mz_list_t *me = mz_malloc(sizeof(*me));

    me->next = me;
    me->prev = me;

    return me;
}

MZ_API void mz_list_add(mz_list_t *new, mz_list_t *head)
{
    mz_list_t *prev = head;
    mz_list_t *next = head->next;

    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

MZ_API void mz_list_del(mz_list_t *entry)
{
    mz_list_t *prev = entry->prev;
    mz_list_t *next = entry->next;

    next->prev = prev;
    prev->next = next;

    entry->next = (mz_list_t *) 0;
    entry->prev = (mz_list_t *) 0;
}

MZ_API void mz_list_replace(mz_list_t *old, mz_list_t *_new)
{
    _new->next = old->next;
    _new->next->prev = _new;
    _new->prev = old->prev;
    _new->prev->next = _new;
}
