#ifndef __MZ_CUNIT_H__
#define __MZ_CUNIT_H__

#include <mz/mz_libs.h>

MZ_API mz_bool mz_cunit_assert_int_(mz_bool is_equal, int expected, int v, const char *file, int line);
MZ_API mz_bool mz_cunit_assert_string_(mz_bool is_equal, const char *expected, const char *v, const char *file, int line);
MZ_API mz_bool mz_cunit_assert_wstring_(mz_bool is_equal, const wchar_t *expected, const wchar_t *v, const char *file, int line);

#define mz_cunit_assert_int(is_equal, expected, v) \
    { if (!mz_cunit_assert_int_(is_equal, expected, v, __FILE__, __LINE__)) return; }

#define mz_cunit_assert_string(is_equal, expected, v) \
    { if (!mz_cunit_assert_string_(is_equal, expected, v, __FILE__, __LINE__)) return; }

#define mz_cunit_assert_wstring(is_equal, expected, v) \
    { if (!mz_cunit_assert_wstring_(is_equal, expected, v, __FILE__, __LINE__)) return; }

#endif
