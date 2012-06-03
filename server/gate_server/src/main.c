#include <stdio.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>

int main(int argc, char **args)
{
    mz_rudp_t *me = mz_rudp_new(YC_SERVER_PORT);
    char buf[YC_BUFFER_SIZE] = {0};
    int ret = 0;

    logI("socket -> %d", me->socket_fd);
    printf("Hello World.\n");

    logI("start looping");

    do {
        mz_memset(buf, 0, YC_BUFFER_SIZE);

        if (0 != (ret = mz_rudp_recv(me, buf, YC_BUFFER_SIZE, NULL)))
            logI("message -> %s", buf);

        logI("ret -> %d", ret);

    } while (strcmp(buf, "quit") != 0);

    logI("exit looping");
    
    return 0;
}
