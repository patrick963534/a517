#include <stdio.h>

extern void unit_test_string();
extern void unit_test_ctype();
extern void unit_test_wchar();
extern void unit_test_wctype();
extern void unit_test_setjmp();

int main()
{
    unit_test_string();
    unit_test_ctype();
    unit_test_wchar();
    //unit_test_wctype();
    //unit_test_setjmp();

    return 0;
}
