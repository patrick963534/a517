#ifndef __TEST_CUNIT_H__
#define __TEST_CUNIT_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>

void test_assert_int_equal()
{
    mz_cunit_assert_int(MZ_TRUE, 193, 193);
    mz_cunit_assert_int(MZ_FALSE, 193, 194);
}

void test_assert_string_equal()
{
    mz_cunit_assert_string(MZ_TRUE, "hello", "hello");
    mz_cunit_assert_string(MZ_FALSE, "hello", "hello2");
    mz_cunit_assert_string(MZ_FALSE, "hello", "world");
}

#endif
