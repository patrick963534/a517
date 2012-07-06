#include "test.h"

void run_test(item_unit_test_t *tests, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        logI("%s", tests[i].name);
        tests[i].test_func();
    }
}


