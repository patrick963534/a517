#include <stdio.h>
#include <stdlib.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <mz/mz_thread.h>
#include <yc/package/yc_config.h>

static void send_test_data(mz_rudp_t *rudp, mz_rudp_addr_t *dst)
{
    int i;
    char buf[YC_BUFFER_SIZE];

    logI("send test data.");

    for (i = 0; i < 20; i++) {
        mz_snprintf(buf, sizeof(buf), "this is test msg: %2d", i);
        mz_rudp_send(rudp, buf, strlen(buf) + 1, dst);
    }
}

static void* thread_run(void *arg)
{
    mz_rudp_t *rudp;
    mz_rudp_addr_t *dst;
    char buf[YC_BUFFER_SIZE];

    rudp = (mz_rudp_t*)arg;
    dst = mz_rudp_addr_new("127.0.0.1", YC_SERVER_PORT);

    mz_time_sleep(1000);
    send_test_data(rudp, dst);

    do {
        scanf("%s", buf);

        mz_rudp_send(rudp, buf, strlen(buf) + 1, dst);
    } while (!mz_string_equal(buf, "client_quit"));

    mz_rudp_addr_delete(dst);
    return NULL;
}

int main(int argc, char **args)
{
    mz_rudp_t *rudp;
    mz_thread_t *thread;
    mz_rudp_addr_t src;
    char buf[YC_BUFFER_SIZE];

    rudp = mz_rudp_new(0);

    assert(rudp->socket_fd > 0 && rudp->socket_fd < 0x8fff);
    logI("message buffer size -> %d", YC_BUFFER_SIZE);

    thread = mz_thread_new(thread_run, "socket_send_thread", rudp);

    do {
        int ret;

        if (-1 != (ret = mz_rudp_recv(rudp, buf, sizeof(buf), &src))) {
            logI("recevie msg -> \"%s\"", buf);
        }
        else {
            mz_time_sleep(33);
        }
    } while (!mz_string_equal(buf, "client_quit"));

    mz_thread_join(thread);
    mz_thread_delete(thread);

    mz_rudp_delete(rudp);

    mz_print_memory_log();
    
    return 0;
}
