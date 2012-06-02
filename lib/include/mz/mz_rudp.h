#ifndef __MZ_RUDP_H__
#define __MZ_RUDP_H__

#include <mz/mz_libs.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

typedef struct mz_rudp_t
{
    int     socket;

} mz_rudp_t;

MZ_API mz_rudp_t* mz_rudp_new(int port);

#endif
