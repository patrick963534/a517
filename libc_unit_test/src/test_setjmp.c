#include <stdio.h>
#include <setjmp.h>
#include <mz/mz_libs.h>
#include <mz/mz_cunit.h>

static jmp_buf buf;

static int first_enter = 0;
static int first_returns = 0;

static int sceond_enter = 0;
static int sceond_returns = 0;

static int static_var = 0;

static void second(void)
{
    sceond_enter = 1;
    longjmp(buf,1);             // jumps back to where setjmp was called - making setjmp now return 1
    //assert_fail("code after longjump() shall never get ran.");
    sceond_returns = 1;
}

static void first(void)
{
    first_enter = 1;
    second();
    printf("code after a function with call to longjump() shall never get ran.");
    first_returns = 1;
}


static void test_setjmp(void)
{
    int stack_var = 0;
    int jret = setjmp(buf);
    stack_var++;    // change to stack var reverted after longjump()
    static_var++;   // change to static var can't reverted by longjump()
    if (!jret)
    {
        mz_cunit_assert_int(MZ_TRUE,1, stack_var);
        mz_cunit_assert_int(MZ_TRUE,1, static_var);
        first();                // when executed, setjmp returns 0
        printf("code after a function with call another function which call to longjump() shall never get ran.");
    }
    else
    {                           // when longjmp jumps back, setjmp returns 1
        mz_cunit_assert_int(MZ_TRUE,1, stack_var);
        mz_cunit_assert_int(MZ_TRUE,2, static_var);
        //assert_true(first_enter);
        //assert_true(sceond_enter);
        //assert_false(sceond_returns);
    }
    mz_cunit_assert_int(MZ_TRUE,1, jret);
}

void unit_test_setjmp()
{
    test_setjmp();
}
