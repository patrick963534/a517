#ifndef __MZ_CUNIT_H__
#define __MZ_CUNIT_H__

#include <mz/libs/mz_defs.h>

MZ_API mz_bool mz_cunit_assert_int_equal_(int expected, int v, const char *file, int line);
MZ_API mz_bool mz_cunit_assert_string_equal_(const char *expected, const char *v, const char *file, int line);

#define mz_cunit_assert_int_equal(expected, v) { if (mz_cunit_assert_int_equal_(expected, v, __FILE__, __LINE__)) return; }
#define mz_cunit_assert_string_equal(expected, v) { if (mz_cunit_assert_string_equal_(expected, v, __FILE__, __LINE__)) return; }

#endif
