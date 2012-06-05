#include <stdio.h>
#include <stdlib.h>
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

    logI("size of origin socket buffer is -> %d", mz_rudp_get_buffer_size(me));
    mz_rudp_set_buffer_size(me, 1024);
    logI("size of socket buffer after set is -> %d", mz_rudp_get_buffer_size(me));

    logI("socket fd is -> %d", me->socket_fd);
    logI("Server -> Start looping");

    do {
        mz_stopwatch_t watch;
        mz_stopwatch_start(&watch);

        mz_memset(msg, 0, YC_BUFFER_SIZE);
        while (-1 != mz_rudp_recv(me, msg, sizeof(msg), &src)) {
            mz_rudp_addr_get_ip(&src, ip, sizeof(ip));

            logI("message -> %s --- ip is -> %s:%d", 
                        msg, ip, mz_rudp_addr_get_port(&src));
        }

        mz_stopwatch_stop(&watch);
        mz_time_sleep(32 - mz_stopwatch_get_ellapse_milliseconds(&watch));

    } while (!mz_string_equal(msg, "quit"));

    logI("exit looping");

    mz_rudp_delete(me);

    atexit(mz_print_memory_log);
    
    return 0;
}
