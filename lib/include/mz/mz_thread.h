#ifndef __MZ_THREAD_H__
#define __MZ_THREAD_H__

#include <mz/libs/mz_defs.h>

typedef struct mz_thread_t
{
    void    *fd;
} mz_thread_t;

typedef struct mz_thread_mutex_t
{
    void    *mutex;
} mz_thread_mutex_t;

typedef void* mz_thread_func_t(void *arg);

MZ_API mz_thread_t* mz_thread_new(mz_thread_func_t func, char *name);
MZ_API void         mz_thread_join(mz_thread_t *me);
MZ_API void         mz_thread_delete(mz_thread_t *me);

MZ_API mz_thread_mutex_t*   mz_thread_mutex_new();
MZ_API void                 mz_thread_mutex_lock(mz_thread_mutex_t *me);
MZ_API void                 mz_thread_mutex_unlock(mz_thread_mutex_t *me);
MZ_API void                 mz_thread_mutex_delete(mz_thread_mutex_t *me);

#endif
