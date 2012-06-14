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
    mz_list_item_t      *pos;
    mz_list_item_t      *bak_pos;
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
MZ_API void             mz_list_iterator_begin(mz_list_t *me);
MZ_API void             mz_list_iterator_next(mz_list_t *me);
MZ_API mz_bool          mz_list_iterator_eof(mz_list_t *me);

#endif
