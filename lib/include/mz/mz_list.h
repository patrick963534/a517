#ifndef __MZ_LIST_H__
#define __MZ_LIST_H__

#include <mz/libs/mz_defs.h>
#include <mz/mz_general_list.h>

typedef struct mz_list_item_t
{
    mz_general_list_t   node;
    void                *ptr_ref;
} mz_list_item_t;

typedef struct mz_list_t
{
    mz_general_list_t   head;
    int                 count;
} mz_list_t;

typedef void (*mz_list_do_func)(void *ptr_ref);

MZ_API mz_list_t*       mz_list_new();
MZ_API void             mz_list_delete(mz_list_t *me);
MZ_API void             mz_list_add(mz_list_t *me, void *v);
MZ_API int              mz_list_position(mz_list_t *me, mz_list_item_t *v);
MZ_API void             mz_list_remove(mz_list_t *me, mz_list_item_t *v);
MZ_API mz_list_item_t*  mz_list_index(mz_list_t *me, int index);
MZ_API void             mz_list_clear(mz_list_t *me);
MZ_API void             mz_list_each_do(mz_list_t *me, mz_list_do_func func);

#define mz_list_entry(ptr, type) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->node)))

#define mz_list_for_each_entry(pos, list_obj, type)  \
            mz_list_for_each_entry_(pos, &list_obj->head, type)  

#define mz_list_for_each_entry_(pos, head, type)    \
    for (pos = mz_list_entry((head)->next, type);  \
        &pos->node != (head);     \
         pos = mz_list_entry(pos->node.next, type))

#define mz_list_for_each_entry_safe(pos, next_pos, list_obj, type)    \
            mz_list_for_each_entry_safe_(pos, next_pos, &list_obj->head, type)

#define mz_list_for_each_entry_safe_(pos, next_pos, head, type)    \
    for (pos = mz_list_entry((head)->next, type), \
         next_pos = mz_list_entry(pos->node.next, type);  \
        &pos->node != (head);     \
         pos = next_pos,    \
         next_pos = mz_list_entry(pos->node.next, type))

#endif
