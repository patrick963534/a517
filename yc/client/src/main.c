#include <stdio.h>
#include <stdlib.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>

static void send_test_data(mz_rudp_t *rudp, mz_rudp_addr_t *dst)
{
    int i;
    char buf[YC_BUFFER_SIZE];

    logI("send test data.");

    for (i = 0; i < 20; i++) {
        mz_snprintf(buf, sizeof(buf), "test msg: %2d", i);
        mz_rudp_send(rudp, buf, strlen(buf) + 1, dst);
    }
}

int main(int argc, char **args)
{
    mz_rudp_t *rudp = mz_rudp_new(0);
    mz_rudp_addr_t *dst = mz_rudp_addr_new("127.0.0.1", YC_SERVER_PORT);

    char buf[YC_BUFFER_SIZE];

    assert(rudp->socket_fd > 0 && rudp->socket_fd < 0x8fff);

    logI("message buffer size -> %d", YC_BUFFER_SIZE);

    mz_time_sleep(1000);
    send_test_data(rudp, dst);

    do {
        mz_memset(buf, 0, sizeof(buf));

        printf("Print message to send: ");
        scanf("%s", buf);

        mz_rudp_send(rudp, buf, strlen(buf) + 1, dst);
    } while (!mz_string_equal(buf, "client_quit"));

    mz_rudp_delete(rudp);
    mz_rudp_addr_delete(dst);

    mz_print_memory_log();
    
    return 0;
}
