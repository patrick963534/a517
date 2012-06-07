#include <stdio.h>
#include <stdlib.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>

int main(int argc, char **args)
{
    mz_rudp_t *me = mz_rudp_new(0);
    mz_rudp_addr_t *dst = mz_rudp_addr_new("127.0.0.1", YC_SERVER_PORT);

    char buf[YC_BUFFER_SIZE];

    assert(me->socket_fd > 0 && me->socket_fd < 0x8fff);


    do {
        mz_memset(buf, 0, sizeof(buf));

        printf("Print message to send: ");
        scanf("%s", buf);

        mz_rudp_send(me, buf, strlen(buf) + 1, dst);
    } while (!mz_string_equal(buf, "client_quit"));

    mz_rudp_delete(me);
    mz_rudp_addr_delete(dst);

    mz_print_memory_log();
    
    return 0;
}
