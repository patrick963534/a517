#ifndef __MZ_RUDP_H__
#define __MZ_RUDP_H__

#include <mz/mz_libs.h>
#include <mz/mz_list.h>

typedef struct mz_rudp_addr_t
{
    int     nl_addr;
    short   ns_port;
} mz_rudp_addr_t;

typedef struct mz_rudp_t
{
    int socket_fd;

} mz_rudp_t;

typedef struct mz_epoll_t
{
    int         epoll_fd;
    mz_list_t   *rudps;
} mz_epoll_t;

typedef void (*mz_epoll_read_func)(mz_rudp_t *rudp, void *arg);

MZ_API mz_epoll_t*  mz_epoll_new();
MZ_API void         mz_epoll_add_readonly(mz_epoll_t *me, mz_rudp_t *rudp);
MZ_API void         mz_epoll_block_wait(mz_epoll_t *me, int timeout, mz_epoll_read_func func);

MZ_API mz_rudp_addr_t*  mz_rudp_addr_new(const char *address, int port);
MZ_API void             mz_rudp_addr_delete(mz_rudp_addr_t *me);
MZ_API const char*      mz_rudp_addr_get_ip(mz_rudp_addr_t *me, char *buf, int sz);
MZ_API int              mz_rudp_addr_get_port(mz_rudp_addr_t *me);

MZ_API int          mz_rudp_get_buffer_size(mz_rudp_t *me);
MZ_API void         mz_rudp_set_buffer_size(mz_rudp_t *me, int new_size);
MZ_API void         mz_rudp_set_no_blocking(mz_rudp_t *me);
MZ_API mz_rudp_t*   mz_rudp_new(int port);
MZ_API int          mz_rudp_recv(mz_rudp_t *me, char *buf, int sz, mz_rudp_addr_t *src);
MZ_API int          mz_rudp_send(mz_rudp_t *me, char *buf, int sz, mz_rudp_addr_t *dst);
MZ_API void         mz_rudp_delete(mz_rudp_t *me);

#endif
