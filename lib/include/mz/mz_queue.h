#ifndef __MZ_QUEUE_H__
#define __MZ_QUEUE_H__

#include <mz/mz_libs.h>
#include <mz/mz_list.h>

typedef struct mz_queue_t
{
    mz_list_t   *root;
} mz_queue_t;

MZ_API mz_queue_t*  mz_queue_new();
MZ_API void         mz_queue_delete(mz_queue_t *me);
MZ_API void         mz_queue_push(mz_queue_t *me, void *value);
MZ_API void*        mz_queue_pop(mz_queue_t *me);
MZ_API void         mz_queue_clear(mz_queue_t *me);

#enfi
