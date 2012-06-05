#include <mz/mz_cunit.h>
#include <mz/libs/mz_log.h>

MZ_API mz_bool mz_cunit_assert_int_(mz_bool is_equal, int expected, int v, const char *file, int line)
{
    mz_bool result = (expected == v);

    if (result != is_equal) {
        if (is_equal)
            logE("File: %s:%d ---> checking EQUAL: but expected value '%d' doesn't equals value '%d'.", file, line, expected, v);
        else
            logE("File: %s:%d ---> checking NOT EQUAL: but expected value '%d' equals value '%d'.", file, line, expected, v);
            
        return MZ_FALSE;
    }

    return MZ_TRUE;
}

MZ_API mz_bool mz_cunit_assert_string_(mz_bool is_equal, const char *expected, const char *v, const char *file, int line)
{
    mz_bool result = MZ_TRUE; 
    const char *a = expected;
    const char *b = v;

    do {

        if (*a != *b) {
            result = MZ_FALSE;
            break;
        }

    } while (*a++ != 0 && *b++ != 0);

    if (result != is_equal) {
        if (is_equal)
            logE("File: %s:%d ---> checking EQUAL: but expected value '%s' doesn't equals value '%s'.", file, line, expected, v);
        else
            logE("File: %s:%d ---> checking NOT EQUAL: but expected value '%s' equals value '%s'.", file, line, expected, v);
   
        return MZ_FALSE;
    }

    return MZ_TRUE;
}
