#include <mz/libs/mz_memory.h>
#include <mz/libs/mz_assert.h>
#include <mz/libs/mz_log.h>
#include <mz/libs/mz_defs.h>
#include "mz_memory_leak_detect.h"
#include <stdlib.h>

MZ_API void mz_print_memory_log()
{
    atexit(report_mem_leak);
}

MZ_API void* mz_malloc_(unsigned int size, const char * file, unsigned int line)
{
    return xcalloc(1, size, file, line);
}

MZ_API void* mz_calloc_(int element, unsigned int size, const char * file, unsigned int line)
{
    return xcalloc(element, size, file, line);
}

MZ_API void* mz_realloc_(void *ptr, unsigned int size, const char * file, unsigned int line)
{
    return xrealloc(ptr, size, file, line);
}

MZ_API void mz_free_(void *ptr)
{
    xfree(ptr);
}
