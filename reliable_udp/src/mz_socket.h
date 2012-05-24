#ifndef __RUDP_SOCKET_H__
#define __RUDP_SOCKET_H__

typedef enum rudp_socket_type_t
{
    rudp_socket_type_client,
    rudp_socket_type_server,
} rudp_socket_type_t;

typedef enum rudp_socket_status_t
{
    rudp_socket_status_none,
    rudp_socket_status_connecting,
    rudp_socket_status_connected,
    rudp_socket_status_disconnect,
} rudp_socket_status_t;

typedef struct rudp_socket_t
{
    int                     socket_fd;
    int                     port;

    int                     dst_addr;
    int                     dst_port;

    rudp_socket_type_t      type;
    rudp_socket_status_t    status;

} rudp_socket_t;

extern rudp_socket_t*   rudp_socket_new(int port, rudp_socket_type_t type);
extern void             rudp_socket_connect(int address, int port);
extern void             rudp_socket_update_status(rudp_socket_t *socket);
extern int              rudp_socket_sendto(rudp_socket_t *socket, const void *msg, int msg_size);
extern int              rudp_socket_recvfrom(rudp_socket_t *socket, const void *msg, int msg_size);

#endif
