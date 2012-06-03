#include <mz/libs/mz_time.h>
#include <mz/libs/mz_log.h>
#include <unistd.h>
#include <time.h>

MZ_API void mz_time_sleep(int milliseconds)
{
    if (milliseconds < 0)
        return;

    usleep(milliseconds * 1000);
}

MZ_API mz_int64 mz_time_get_tick()
{
    static struct timespec init = {0, 0};
    struct timespec t;

    if (init.tv_sec == 0 && init.tv_nsec == 0) {
        clock_gettime(CLOCK_REALTIME, &init);
    }

    clock_gettime(CLOCK_REALTIME, &t);

    return (mz_int64)((t.tv_sec - init.tv_sec) * 1000 + (t.tv_nsec - init.tv_nsec) / 1000000);
}
