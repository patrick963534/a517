#include <stdio.h>
#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_general_list.h>
#include "test_cunit.h"

typedef void (*test_func_t)();

typedef struct test_unit_t
{
    test_func_t test_func;
    mz_general_list_t   element;
} test_unit_t;

static test_unit_t *root;
static int test_count;

static void add_test(test_func_t func)
{
    test_unit_t *me = mz_malloc(sizeof(*me));
    mz_general_list_init(&me->element);
    me->test_func = func;

    mz_general_list_add(&me->element, &root->element);
}

static void run_test()
{
    test_unit_t *pos;
    test_count = 0;

    mz_general_list_for_each_entry(pos, &root->element, test_unit_t, element) {
        pos->test_func();
        test_count++;
    }
}

int main()
{
    root = mz_malloc(sizeof(*root));
    mz_general_list_init(&root->element);
    

    logI("Start Unit Test");
    logI("------------------------------");

    add_test(test_assert_int_equal);
    add_test(test_assert_string_equal);

    run_test();
    logI("Total test: %d.", test_count);

    logI("------------------------------");
    return 0;
}
