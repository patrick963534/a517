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

    //mz_time_sleep(10 * 1000);

    do {
        int tick = mz_time_get_tick();

        mz_memset(msg, 0, YC_BUFFER_SIZE);
        while (-1 != mz_rudp_recv(me, msg, sizeof(msg), &src)) {
            mz_rudp_addr_get_ip(&src, ip, sizeof(ip));

            logI("message -> %s --- ip is -> %s:%d", msg, ip, mz_rudp_addr_get_port(&src));
        }

        mz_time_sleep(32 - (tick - mz_time_get_tick()));

    } while (strcmp(msg, "quit") != 0);

    logI("exit looping");
    
    return 0;
}
