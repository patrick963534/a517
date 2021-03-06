#ifndef __TEST_DICTIONARY_H__
#define __TEST_DICTIONARY_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_dictionary.h>

typedef struct item2_t
{
    int id;
} item2_t;

void test_dictionary()
{
    mz_dictionary_t *me;
    int i;

    me = mz_dictionary_new();

    for (i = 0; i < 5; i++) {
        char buf[8];
        item2_t *it = mz_malloc(sizeof(*it));
        it->id = i;
        mz_snprintf(buf, sizeof(buf), "%d", i);
        mz_dictionary_add(me, buf, it);
    }

    for (i = 0; i < 5; i++) {
        char buf[8];
        item2_t *it;

        mz_snprintf(buf, sizeof(buf), "%d", i);
        it = (item2_t*)mz_dictionary_contains(me, buf);

        mz_cunit_assert_int(MZ_TRUE, i, it->id);
    }

    mz_dictionary_each_do(me, mz_free);
    mz_dictionary_delete(me);
}

#endif
