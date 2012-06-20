#ifndef __MZ_STRING_H__
#define __MZ_STRING_H__

#include <mz/libs/mz_defs.h>
#include <string.h>

MZ_API const char*      mz_strcopy(char *buf, const char *src, int sz);
MZ_API char*            mz_strdup(const char *str);
MZ_API int              mz_strlen(const char *str);
MZ_API char*            mz_strchr(const char *str, int ch);
MZ_API const char*      mz_strtoken(char *str, const char *delim);
MZ_API mz_bool          mz_strequal(const char *str1, const char *str2);
MZ_API char*            mz_strtrim(const char *str, int fail_value);
MZ_API int              mz_strto_int(const char *str, int fail_value);
MZ_API const char*      mz_strfrom_int(int value, char *buf, int sz);
MZ_API mz_bool          mz_strcontains(const char *str, const char *target);

MZ_API int              mz_snprintf(char *buf, int sz, const char *format, ...);

#endif
