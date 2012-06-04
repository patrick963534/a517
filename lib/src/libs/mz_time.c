#include <mz/libs/mz_time.h>
#include <mz/libs/mz_log.h>
#include <unistd.h>
#include <time.h>

MZ_API void mz_stopwatch_start(mz_stopwatch_t *me)
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    me->start = t.tv_sec * 1000000 + t.tv_nsec / 1000;
}

MZ_API void mz_stopwatch_stop(mz_stopwatch_t *me)
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    me->end = t.tv_sec * 1000000 + t.tv_nsec / 1000;
}

MZ_API int mz_stopwatch_get_ellapse_milliseconds(mz_stopwatch_t *me)
{
    return (int)((me->end - me->start) / 1000);
}

MZ_API void mz_time_sleep(int milliseconds)
{
    if (milliseconds < 0)
        return;

    usleep(milliseconds * 1000);
}
