#include <mz/mz_thread.h>
#include <mz/mz_libs.h>
#include <pthread.h>

MZ_API mz_thread_t* mz_thread_new(mz_thread_func_t func, char *name)
{
    mz_thread_t *me = mz_malloc(sizeof(*me));
    me->fd = mz_malloc(sizeof(pthread_t));

    pthread_create((pthread_t*)me->fd, NULL, func, name);

    return me;
}

MZ_API void mz_thread_join(mz_thread_t *me)
{
    pthread_join(*((pthread_t*)me->fd), NULL);
}

MZ_API void mz_thread_delete(mz_thread_t *me)
{
    pthread_cancel(*((pthread_t*)me->fd));
    mz_free(me->fd);
    mz_free(me);
}

MZ_API mz_thread_mutex_t* mz_thread_mutex_new()
{
    mz_thread_mutex_t *me = mz_malloc(sizeof(*me));
    me->mutex = mz_malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init((pthread_mutex_t*)me->mutex, NULL);

    return me;
}

MZ_API void mz_thread_mutex_lock(mz_thread_mutex_t *me)
{
    pthread_mutex_lock((pthread_mutex_t*)me->mutex);
}

MZ_API void mz_thread_mutex_unlock(mz_thread_mutex_t *me)
{
    pthread_mutex_unlock((pthread_mutex_t*)me->mutex);
}

MZ_API void mz_thread_mutex_delete(mz_thread_mutex_t *me)
{
    pthread_mutex_destroy((pthread_mutex_t*)me->mutex);

    mz_free(me->mutex);
    mz_free(me);
}
