#include <mz/mz_cunit.h>
#include <mz/libs/mz_log.h>

MZ_API mz_bool mz_cunit_assert_int_equal_(int expected, int v, const char *file, int line)
{
    if (expected != v) {
        logI("File: %s:%d ---> expected is '%d', but -> '%d'.", file, line, expected, v);
        return 1;
    }

    return 0;
}

MZ_API mz_bool mz_cunit_assert_string_equal_(const char *expected, const char *v, const char *file, int line)
{
    const char *a = expected;
    const char *b = v;




    return 0;
}
