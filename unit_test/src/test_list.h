#ifndef __TEST_LIST_H__
#define __TEST_LIST_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>

typedef struct item_t
{
    int id;
} item_t;

void test_list_count()
{
    mz_list_t *me = mz_list_new();
    int i;

    for (i = 0; i < 5; i++) {
        item_t *it = mz_malloc(sizeof(*it));
        it->id = i;
        mz_list_add(me, it);
    }

    mz_cunit_assert_int(MZ_TRUE, 5, me->count);

    mz_list_clear(me);
    mz_list_delete(me);
}

void test_list_ptr_ref_remove()
{
    
}

#endif
