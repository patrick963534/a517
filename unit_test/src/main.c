#include <stdio.h>
#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>
#include "test_cunit.h"

typedef void (*test_func_t)();

static mz_list_t *root;
static int test_count;

static void run_test()
{
    mz_list_element_ptr_ref_t *pos;
    test_count = 0;

    mz_list_for_each_entry(pos, &root->head, mz_list_element_ptr_ref_t) {
        ((test_func_t)pos->ptr_ref)();
        test_count++;
    }
}

int main()
{
    root = mz_list_new(mz_list_element_type_ptr_ref);
    
    logI("Start Unit Test");
    logI("------------------------------");

    mz_list_add_ptr_ref(root, test_assert_int_equal);
    mz_list_add_ptr_ref(root, test_assert_string_equal);

    run_test();
    logI("Total test: %d.", test_count);

    logI("------------------------------");
    return 0;
}
