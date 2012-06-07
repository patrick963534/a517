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

static void* thread_run(void *arg)
{
    mz_rudp_t *rudp;
    yc_msg_pool_t* msg_pool;

    mz_rudp_addr_t src;
    char msg[YC_BUFFER_SIZE];

    struct epoll_event ev, events[EVENT_COUNT];
    int epfd;
    int nfds, i;
    
    msg_pool= (yc_msg_pool_t*)arg;
    
    mz_list_index(msg_pool->queue, 0);
    rudp = mz_rudp_new(YC_SERVER_PORT);
    mz_rudp_set_buffer_size(rudp, 1024);
    mz_rudp_set_no_blocking(rudp);

    {
        epfd = epoll_create(256);
        ev.data.fd = rudp->socket_fd;
        ev.events = EPOLLIN;

        epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
    }

    add_preparing_msg(msg_pool);

    do {
        int ret_sz;
        mz_bool is_quit;

        nfds = epoll_wait(epfd, events, EVENT_COUNT, 30);

        for (i = 0; i < nfds; i++) {
            if (events[i].data.fd == rudp->socket_fd) {
                if (-1 != (ret_sz = mz_rudp_recv(rudp, msg, sizeof(msg), &src))) {
                    yc_msg_pool_end_queue(msg_pool, yc_msg_pool_item_new(msg, ret_sz));

                    if (!is_quit)
                        is_quit = mz_string_equal(msg, quit_string);
                }
            }
        }

        if (is_quit)
            break;
        
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

static void basic_way()
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
}

int main(int argc, char **args)
{
    mz_unused(basic_way);
    mz_unused(epoll_way);

    epoll_way();  
    mz_print_memory_log();
    return 0;
}
