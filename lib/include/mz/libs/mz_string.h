#ifndef __MZ_STRING_H__
#define __MZ_STRING_H__

#include <mz/libs/mz_defs.h>
#include <string.h>

MZ_API const char*      mz_string_copy(char *buf, const char *src, int sz);
MZ_API char*            mz_string_dup(const char *str);
MZ_API int              mz_string_len(const char *str);
MZ_API char*            mz_string_chr(const char *str, int ch);
MZ_API const char*      mz_string_token(char *str, const char *delim);
MZ_API mz_bool          mz_string_equal(const char *str1, const char *str2);
MZ_API char*            mz_string_trim(const char *str, int fail_value);
MZ_API int              mz_string_to_int(const char *str, int fail_value);
MZ_API const char*      mz_string_from_int(int value, char *buf, int sz);
MZ_API mz_bool          mz_string_contains(const char *str, const char *target);

MZ_API int              mz_snprintf(char *buf, int sz, const char *format, ...);

#endif
