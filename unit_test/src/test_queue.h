#ifndef __TEST_QUEUE_H__
#define __TEST_QUEUE_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_queue.h>

typedef struct item3_t
{
    int id;
} item3_t;

void test_queue_push_and_pop()
{
    mz_queue_t *me = mz_queue_new();
    int count = 50;
    int i;

    for (i = 0; i < count; i++) {
        item3_t *it = mz_malloc(sizeof(*it));
        it->id = i;
        mz_queue_push(me, it);
    }

    for (i = 0; i < count; i++) {
        void *v = mz_queue_pop(me);
        mz_cunit_assert_int(MZ_TRUE, i, ((item3_t*)v)->id);
        mz_free(v);
    }

    mz_queue_delete(me);
}

#endif
