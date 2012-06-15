#include <stdio.h>
#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>
#include "test_cunit.h"
#include "test_list.h"
#include "test_dictionary.h"
#include "test_queue.h"

typedef void (*test_func_t)();

typedef struct test_unit_t
{
    test_func_t test_func;
    const char  *name;
} test_unit_t;

#define add_unit_test(root, func_name)    \
    {   \
        test_unit_t *me = mz_malloc(sizeof(*me));         \
        me->test_func = func_name;  \
        me->name = #func_name; \
        mz_list_add(root, me);                  \
    }

static mz_list_t *root;
static int test_count;

static void run_test()
{
    test_unit_t *t;
    test_count = 0;

    mz_list_iterator_begin(root);
    while (!mz_list_iterator_eof(root)) {
        t = (test_unit_t*)mz_list_iterator_current(root);
        t->test_func();
        logI("%s", t->name);
        test_count++;

        mz_list_iterator_next(root);
    }
}

int main()
{
    root = mz_list_new();
    
    logI("Start Unit Test");
    logI("------------------------------");

    add_unit_test(root, test_assert_int_equal);
    add_unit_test(root, test_assert_string_equal);
    add_unit_test(root, test_list_count);
    add_unit_test(root, test_list_index);
    add_unit_test(root, test_queue_push_and_pop);

    run_test();
    logI("Total test: %d.", test_count);
    logI("------------------------------");
    
    mz_list_each_do(root, mz_free);
    mz_list_delete(root);

    mz_print_memory_log();
    return 0;
}
