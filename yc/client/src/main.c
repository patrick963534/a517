#include <stdio.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>

int main(int argc, char **args)
{
    mz_rudp_t *me = mz_rudp_new(0);
    mz_rudp_addr_t *dst = mz_rudp_addr_new("127.0.0.1", YC_SERVER_PORT);

    char buf[YC_BUFFER_SIZE] = {0};
    int ret;

    logI("socket -> %d", me->socket_fd);
    printf("Hello World.\n");

    {
        int i;
        for (i = 0; i < 1000; i++) {
            mz_snprintf(buf, sizeof(buf), "good moring -> %d.", i);
            //ret = mz_rudp_send(me, buf, sizeof(buf), dst);
            //logI("send -> %s", buf);
        }
    }

    do {
        mz_memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        ret = mz_rudp_send(me, buf, strlen(buf) + 1, dst);
        logI("send -> %s", buf);
        logI("ret  -> %d", ret);

    } while (strcmp(buf, "quit") != 0);

    
    return 0;
}
