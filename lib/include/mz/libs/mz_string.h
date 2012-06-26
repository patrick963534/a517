#ifndef __MZ_STRING_H__
#define __MZ_STRING_H__

#include <mz/libs/mz_defs.h>
#include <string.h>

typedef struct mz_string_t
{
    char    *str;
    int     nstr;
    int     increase_step;
} mz_string_t;

MZ_API mz_string_t* mz_string_new();
MZ_API void mz_string_delete(mz_string_t *me);
MZ_API void mz_string_append_char(mz_string_t *me, char ch);
MZ_API void mz_string_append_char_array(mz_string_t *me, char *char_array, int array_sz);
MZ_API void mz_string_append_string(mz_string_t *me, mz_string_t *dst);

MZ_API const char*      mz_strcopy(char *buf, const char *src, int sz);
MZ_API char*            mz_strdup(const char *str);
MZ_API int              mz_strlen(const char *str);
MZ_API char*            mz_strchr(const char *str, int ch);
MZ_API char*            mz_strrchr(const char *str, int ch);
MZ_API const char*      mz_strtoken(char *str, const char *delim);
MZ_API mz_bool          mz_strequal(const char *str1, const char *str2);
MZ_API char*            mz_strtrim(const char *str, int fail_value);
MZ_API int              mz_strto_int(const char *str, int fail_value);
MZ_API const char*      mz_strfrom_int(int value, char *buf, int sz);
MZ_API mz_bool          mz_strcontains(const char *str, const char *target);

MZ_API int              mz_snprintf(char *buf, int sz, const char *format, ...);

#endif
