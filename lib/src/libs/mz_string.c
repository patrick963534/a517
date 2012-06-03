#include <mz/libs/mz_string.h>
#include <stdarg.h>

MZ_API int mz_snprintf(char *buf, int sz, const char *format, ...)
{
    va_list va;

    va_start(va, format);
    vsnprintf(buf, sz, format, va);
    va_end(va);
}

MZ_API const char* mz_string_copy(char *buf, const char *src, int sz)
{
    return strncpy(buf, src, sz);
}
