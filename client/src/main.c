#include <stdio.h>
#include <mz/mz_rudp.h>

int main(int argc, char **args)
{
    mz_rudp_t *me = mz_rudp_new(3000);

    printf("Hello World.\n");


    return 0;
}
