#include <stdio.h>
#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>
#include "test_cunit.h"
#include "test_list.h"

typedef void (*test_func_t)();

typedef struct test_unit_t
{
    test_func_t test_func;
    const char  *name;
} test_unit_t;

#define add_unit_test(root, func_name, tag)    \
    {   \
        test_unit_t *me = mz_malloc(sizeof(*me));         \
        me->test_func = func_name;  \
        me->name = tag; \
        mz_list_add_ptr_ref(root, me);                  \
    }

static mz_list_t *root;
static int test_count;

static void run_test()
{
    mz_list_item_ptr_ref_t *pos, *next_pos;
    test_count = 0;

    mz_list_for_each_entry_safe(pos, next_pos, root, mz_list_item_ptr_ref_t) {
        test_unit_t *t = (test_unit_t*)pos->ptr_ref;
        logI("%s", t->name);
    }

    //mz_list_for_each_entry(pos, root, mz_list_item_ptr_ref_t) {
    //    test_unit_t *t = (test_unit_t*)pos->ptr_ref;
    //    t->test_func();
    //    logI("%s", t->name);
    //    test_count++;
    //}
}

int main()
{
    root = mz_list_new_ptr_ref();
    
    logI("Start Unit Test");
    logI("------------------------------");

    add_unit_test(root, test_assert_int_equal, "int equal");
    add_unit_test(root, test_assert_string_equal, "string equal");
    add_unit_test(root, test_list_count, "list count");

    run_test();
    logI("Total test: %d.", test_count);

    logI("------------------------------");

    mz_list_delete(root);

    mz_print_memory_log();
    return 0;
}
