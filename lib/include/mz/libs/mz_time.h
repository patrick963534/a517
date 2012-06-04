#ifndef __MZ_TIME_H__
#define __MZ_TIME_H__

#include <mz/libs/mz_defs.h>

typedef struct mz_stopwatch_t
{
    mz_int64    start;
    mz_int64    end;
} mz_stopwatch_t;

MZ_API void mz_stopwatch_start(mz_stopwatch_t *me);
MZ_API void mz_stopwatch_stop(mz_stopwatch_t *me);
MZ_API int  mz_stopwatch_get_ellapse_milliseconds(mz_stopwatch_t *me);

MZ_API void mz_time_sleep(int milliseconds);

#endif
