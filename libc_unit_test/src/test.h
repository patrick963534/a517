#ifndef __LIBC_TEST_H__
#define __LIBC_TEST_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>

#include <stdio.h>
#include <string.h>

typedef void (*cunit_item_test)();

typedef struct item_unit_test_t
{
    const char *name;
    cunit_item_test test_func;
} item_unit_test_t;

#define macro_item_unit(t_)   \
    { #t_, t_ }

void run_test(item_unit_test_t *tests, int count);

#endif
