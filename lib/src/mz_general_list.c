#include <mz/mz_general_list.h>
#include <mz/libs/mz_memory.h>
#include <mz/libs/mz_defs.h>

MZ_API void mz_general_list_init(mz_general_list_t *me)
{
    me->next = me;
    me->prev = me;
}

MZ_API void mz_general_list_add(mz_general_list_t *new, mz_general_list_t *head)
{
    mz_general_list_t *prev = head->prev;
    mz_general_list_t *next = head;

    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

MZ_API void mz_general_list_remove(mz_general_list_t *entry)
{
    mz_general_list_t *prev = entry->prev;
    mz_general_list_t *next = entry->next;

    next->prev = prev;
    prev->next = next;

    entry->next = (mz_general_list_t *) 0;
    entry->prev = (mz_general_list_t *) 0;
}

MZ_API void mz_general_list_replace(mz_general_list_t *old, mz_general_list_t *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

MZ_API void mz_general_list_delete(mz_general_list_t *me)
{
    mz_free(me);
}
