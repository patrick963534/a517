#include <stdio.h>
#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>
#include "test_cunit.h"

typedef void (*test_func_t)();

typedef struct test_unit_t
{
    test_func_t test_func;
    mz_list_t   *element;
} test_unit_t;

static test_unit_t *root;
static int test_count;

static void add_test(test_func_t func)
{
    test_unit_t *me = mz_malloc(sizeof(*me));
    me->element = mz_list_new();
    me->test_func = func;

    if (root == NULL)
        root = me;
    else
        mz_list_add(me->element, root->element);
}

static void run_test()
{
    //test_unit_t *pos;
    test_count = 0;

    //mz_list_for_each_entry(pos, root->element, test_unit_t, element) {
    //    pos->test_func();
    //    test_count++;
    //}
}

int main()
{
    logI("Start Unit Test");
    logI("------------------------------");

    add_test(test_assert_int_equal);
    add_test(test_assert_string_equal);

    run_test();
    logI("Total test: %d.", test_count);

    logI("------------------------------");
    return 0;
}
