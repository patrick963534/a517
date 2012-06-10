#include <stdio.h>
#include <stdlib.h>
#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <yc/package/yc_config.h>
#include "msg_pool.h"

#include <sys/epoll.h>
#define EVENT_COUNT 20

static const char *quit_string = "server_quit";

typedef struct socket_thread_data_t
{
    yc_msg_pool_t   *msg_pool;
    mz_bool         is_quit;
} socket_thread_data_t;

//static void add_preparing_msg(yc_msg_pool_t *msg_pool)
//{
//    yc_msg_pool_item_t *it1, *it2, *it3;
//    int delay = 200;
//    char *msg[3];
//
//    msg[0] = "test msg: item 1 data.";
//    msg[1] = "test msg: item 2 data.";
//    msg[2] = "test msg: item 3 data.";
//
//    it1 = yc_msg_pool_item_new(msg[0], mz_string_len(msg[0]) + 1);
//    it2 = yc_msg_pool_item_new(msg[1], mz_string_len(msg[1]) + 1);
//    it3 = yc_msg_pool_item_new(msg[2], mz_string_len(msg[2]) + 1);
//
//    yc_msg_pool_end_queue(msg_pool, it1);
//    mz_time_sleep(delay);
//    yc_msg_pool_end_queue(msg_pool, it2);
//    mz_time_sleep(delay);
//    yc_msg_pool_end_queue(msg_pool, it3);
//}

static void rudp_read_data(mz_rudp_t *rudp, void *arg)
{
    int ret_sz;
    char msg[YC_BUFFER_SIZE];
    socket_thread_data_t *td;
    mz_rudp_addr_t src;
    
    td = (socket_thread_data_t*)arg;

    if (-1 != (ret_sz = mz_rudp_recv(rudp, msg, sizeof(msg), &src))) {
        yc_msg_pool_item_t *it = yc_msg_pool_item_new(msg, ret_sz);
        it->rudp = rudp;
        it->from_addr = src;

        yc_msg_pool_end_queue(td->msg_pool, it);

        td->is_quit = mz_string_equal(msg, quit_string);
    }
}

static void* thread_run(void *arg)
{
    mz_rudp_t *rudp;
    mz_epoll_t *epoll;
    socket_thread_data_t *td;

    td = (socket_thread_data_t*)arg;
    
    rudp = mz_rudp_new(YC_SERVER_PORT);
    mz_rudp_set_buffer_size(rudp, YC_SOCKET_BUFFER_SIZE);
    mz_rudp_set_no_blocking(rudp);

    epoll = mz_epoll_new();
    mz_epoll_add_readonly(epoll, rudp);

    do {
        mz_epoll_block_wait(epoll, 30, rudp_read_data, td);
    } while (!td->is_quit);

    mz_rudp_delete(rudp);
    mz_epoll_delete(epoll);

    return NULL;
}

static void epoll_way()
{
    mz_thread_t *thread;
    yc_msg_pool_item_t *msg;
    socket_thread_data_t *td;
    char buf[YC_BUFFER_SIZE];

    td = mz_malloc(sizeof(*td));
    td->msg_pool = yc_msg_pool_new();

    thread = mz_thread_new(thread_run, "socket_thread", td);

    while (1) {
        while (NULL != (msg = yc_msg_pool_pop(td->msg_pool))) {
            if (!mz_string_equal(msg->data, "client_quit"))
                mz_snprintf(buf, sizeof(buf), "server reply: \"%s\" -> msg_pool_count:%-5d", msg->data, yc_msg_pool_count(td->msg_pool));
            else
                mz_snprintf(buf, sizeof(buf), "%s", msg->data);
        
            mz_rudp_send(msg->rudp, buf, mz_string_len(buf) + 1, &msg->from_addr);
            logI("%s -> send to client.", buf);

            yc_msg_pool_item_delete(msg);
        }

        if (td->is_quit && yc_msg_pool_count(td->msg_pool) == 0)
            break;

        mz_time_sleep(33);
    }

    mz_thread_join(thread);
    mz_thread_delete(thread);

    yc_msg_pool_delete(td->msg_pool);
    mz_free(td);

    logI("main thread exit");
}

int main(int argc, char **args)
{
    epoll_way();  
    mz_print_memory_log();
    return 0;
}
