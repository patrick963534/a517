#include <mz/libs/mz_string.h>
#include <mz/libs/mz_memory.h>
#include <stdio.h>
#include <stdarg.h>

MZ_API mz_string_t* mz_string_new()
{
    mz_string_t *me = calloc(1, sizeof(*me));
    me->increase_step = 64;
    me->str = calloc(1, me->increase_step);
    me->str[0] = '\0';

    return me;
}

MZ_API void mz_string_delete(mz_string_t *me)
{
    free(me->str);
    free(me);
}

static void update_string_cache(mz_string_t *me, int input_sz)
{
    int is_leak = 0;

    while (me->nstr + 1 + input_sz >= me->increase_step - 1) {
        me->increase_step += me->increase_step;
        is_leak = 1;
    }
    
    if (is_leak)
        me->str = realloc(me->str, me->increase_step);
}

MZ_API void mz_string_append_char(mz_string_t *me, char ch)
{
    update_string_cache(me, 1);

    me->str[me->nstr++] = ch;
    me->str[me->nstr] = '\0';
}

MZ_API void mz_string_append_chararray(mz_string_t *me, char *char_array, int array_sz)
{
    char *src = me->str + me->nstr;
    char *dst = char_array;
    int i = array_sz;

    update_string_cache(me, array_sz);

    while (i-- > 0) 
        *src++ = *dst++;

    me->nstr += array_sz;
    me->str[me->nstr] = '\0';
}

MZ_API void mz_string_append_string(mz_string_t *me, mz_string_t *dst_string)
{
    char *src = me->str + me->nstr;
    char *dst = dst_string->str;

    update_string_cache(me, dst_string->nstr);

    while (*dst != 0) 
        *src++ = *dst++;

    me->nstr += dst_string->nstr;
    me->str[me->nstr] = '\0';
}

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
