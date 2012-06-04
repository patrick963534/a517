#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

MZ_API void mz_rudp_set_no_blocking(mz_rudp_t *me)
{
    int sock = me->socket_fd;
    int opts;

    if ((opts = fcntl(sock, F_GETFL)) < 0) 
        goto error;

    opts = opts|O_NONBLOCK;

    if(fcntl(sock, F_SETFL, opts) < 0)
        goto error;

    return;

error:
    logE("Fail to set non blocking for socket.");
}


static struct sockaddr_in get_sockaddr(int port)
{
    struct sockaddr_in addr; 

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    return addr;
}

MZ_API int mz_rudp_set_buffer_size(mz_rudp_t *me, int new_size)
{
    setsockopt(me->socket_fd, SOL_SOCKET, SO_SNDBUF, &new_size, sizeof(new_size));
}

MZ_API int mz_rudp_get_buffer_size(mz_rudp_t *me)
{
    int buff;
    int optlen = sizeof(buff);
    getsockopt(me->socket_fd, SOL_SOCKET, SO_SNDBUF, &buff, &optlen);

    return buff;
}

MZ_API mz_rudp_t* mz_rudp_new(int port)
{
    mz_rudp_t *me = mz_malloc(sizeof(*me));
    struct sockaddr_in addr = get_sockaddr(port);

    if (-1 == (me->socket_fd = socket(AF_INET, SOCK_DGRAM, 0)))
        goto error;

    if (-1 == bind(me->socket_fd, (struct sockaddr*)&addr, sizeof(addr)))
        goto error;

    return me;

error:

    logE("Fail to create or bind a rudp object");
    mz_assert(NULL);

    return NULL;
}

MZ_API void  mz_rudp_delete(mz_rudp_t *me)
{
    close(me->socket_fd);
    mz_free(me);
}

MZ_API int mz_rudp_recv(mz_rudp_t *me, char *buf, int sz, mz_rudp_addr_t *src)
{
    struct sockaddr_in from;
    socklen_t len = sizeof(from);

    int ret = recvfrom(me->socket_fd, buf, sz, 0, (struct sockaddr*)&from, &len);

    if (src) {
        src->nl_addr = from.sin_addr.s_addr;
        src->ns_port = from.sin_port;
    }

    if (ret > 0 && ret != sz)
        logI("size of receiving data is -> %d", ret);

    return ret;
}

MZ_API int mz_rudp_send(mz_rudp_t *me, char *buf, int sz, mz_rudp_addr_t *dst)
{
    struct sockaddr_in addr; 
    int ret;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = dst->nl_addr;
    addr.sin_port = dst->ns_port;

    ret = sendto(me->socket_fd, buf, sz, 0, (struct sockaddr*)&addr, sizeof(addr));

    return ret;
}

MZ_API const char* mz_rudp_addr_get_ip(mz_rudp_addr_t *me, char *buf, int sz)
{
    int v = me->nl_addr;

    mz_snprintf(buf, sz, "%d.%d.%d.%d", 
                    (v&0xff), 
                    (v&0xff00) >> 8, 
                    (v&0xff0000) >> 16, 
                    (v&0xff000000) >> 24); 

    return buf;
}

MZ_API mz_rudp_addr_t* mz_rudp_addr_new(const char *address, int port)
{
    mz_rudp_addr_t *me = mz_malloc(sizeof(*me));
    
    struct sockaddr_in addr; 
    inet_aton(address, &addr.sin_addr);

    me->nl_addr = addr.sin_addr.s_addr;
    me->ns_port = htons(port);

    return me;
}

MZ_API int mz_rudp_addr_get_port(mz_rudp_addr_t *me)
{
    return ntohs(me->ns_port);
}
