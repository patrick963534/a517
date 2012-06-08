#include <stdio.h>
#include <stdlib.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>
#include "msg_pool.h"

#include <sys/epoll.h>
#define EVENT_COUNT 20

static const char *quit_string = "server_quit";

static void add_preparing_msg(yc_msg_pool_t *msg_pool)
{
    yc_msg_pool_item_t *it1, *it2, *it3;
    int delay = 200;
    char *msg[3];

    msg[0] = "test msg: item 1 data.";
    msg[1] = "test msg: item 2 data.";
    msg[2] = "test msg: item 3 data.";

    it1 = yc_msg_pool_item_new(msg[0], mz_string_len(msg[0]) + 1);
    it2 = yc_msg_pool_item_new(msg[1], mz_string_len(msg[1]) + 1);
    it3 = yc_msg_pool_item_new(msg[2], mz_string_len(msg[2]) + 1);

    yc_msg_pool_end_queue(msg_pool, it1);
    mz_time_sleep(delay);
    yc_msg_pool_end_queue(msg_pool, it2);
    mz_time_sleep(delay);
    yc_msg_pool_end_queue(msg_pool, it3);
}

static void rudp_read_data(mz_rudp_t *rudp, void *arg)
{
    int ret_sz;
    char msg[YC_BUFFER_SIZE];
    yc_msg_pool_t *msg_pool;
    mz_rudp_addr_t src;
    
    msg_pool = (yc_msg_pool_t*)arg;

    if (-1 != (ret_sz = mz_rudp_recv(rudp, msg, sizeof(msg), &src))) {
        yc_msg_pool_end_queue(msg_pool, yc_msg_pool_item_new(msg, ret_sz));
    }
}

static void* thread_run(void *arg)
{
    mz_rudp_t *rudp;
    mz_epoll_t *epoll;
    yc_msg_pool_t *msg_pool;

    msg_pool= (yc_msg_pool_t*)arg;
    add_preparing_msg(msg_pool);
    
    rudp = mz_rudp_new(YC_SERVER_PORT);
    mz_rudp_set_buffer_size(rudp, 1024);
    mz_rudp_set_no_blocking(rudp);

    epoll = mz_epoll_new();
    mz_epoll_add_readonly(epoll, rudp);

    do {
        mz_epoll_block_wait(epoll, 30, rudp_read_data, msg_pool);
    } while (1);

    mz_rudp_delete(rudp);

    return NULL;
}

static void epoll_way()
{
    mz_thread_t *thread;
    yc_msg_pool_item_t *msg;
    yc_msg_pool_t* msg_pool;

    msg_pool = yc_msg_pool_new();

    thread = mz_thread_new(thread_run, "socket_thread", msg_pool);

    while (1) {
        msg = yc_msg_pool_pop(msg_pool);

        if (msg != NULL) {
            mz_bool is_quit = mz_string_equal(msg->data, quit_string);
            logI("%s -> %d", msg->data, msg->ndata);
            yc_msg_pool_item_delete(msg);

            if (is_quit) 
                break;
        }
        else {
            mz_time_sleep(33);
        }
    }

    mz_thread_join(thread);
    mz_thread_delete(thread);

    yc_msg_pool_delete(msg_pool);
}

int main(int argc, char **args)
{
    epoll_way();  
    mz_print_memory_log();
    return 0;
}
