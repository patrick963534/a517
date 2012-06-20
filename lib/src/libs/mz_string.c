#include <mz/libs/mz_string.h>
#include <mz/libs/mz_memory.h>
#include <stdio.h>
#include <stdarg.h>

MZ_API int mz_snprintf(char *buf, int sz, const char *format, ...)
{
    va_list va;
    int ret;

    va_start(va, format);
    ret = vsnprintf(buf, sz, format, va);
    va_end(va);

    return ret;
}

MZ_API const char* mz_strcopy(char *buf, const char *src, int sz)
{
    return strncpy(buf, src, sz);
}

MZ_API mz_bool mz_strequal(const char *str1, const char *str2)
{
    return strcmp(str1, str2) == 0;
}

MZ_API char* mz_strdup(const char *str)
{
    if (str == NULL) {
        return NULL;
    }
    else {
        int sz = strlen(str) + 1;
        char *v = mz_malloc(sz);
        strncpy(v, str, sz);

        return v;
    }
}

MZ_API int mz_strlen(const char *str)
{
    return strlen(str);
}

MZ_API mz_bool mz_strcontains(const char *str, const char *target)
{
    return strstr(str, target) != NULL;
}
