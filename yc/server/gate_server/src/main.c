#include <stdio.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>

int main(int argc, char **args)
{
    mz_rudp_t *me = mz_rudp_new(YC_SERVER_PORT);
    mz_rudp_addr_t src;

    char msg[YC_BUFFER_SIZE];
    char ip[YC_BUFFER_SIZE];

    mz_rudp_set_no_blocking(me);

    logI("socket -> %d", me->socket_fd);
    logI("start looping");

    do {
        mz_memset(msg, 0, YC_BUFFER_SIZE);

        if (-1 != mz_rudp_recv(me, msg, YC_BUFFER_SIZE, &src)) {
            logI("message -> %s", msg);

            mz_rudp_addr_get_ip(&src, ip, sizeof(ip));
            logI("ip is -> %s", ip);
        }

    } while (strcmp(msg, "quit") != 0);

    logI("exit looping");
    
    return 0;
}
