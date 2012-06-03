#ifndef __MZ_RUDP_MANAGER_H__
#define __MZ_RUDP_MANAGER_H__

#include <mz/mz_rudp.h>
#include <mz/mz_libs.h>

typedef struct mz_rudp_manager_t
{

} mz_rudp_manager_t;

MZ_API mz_rudp_manager_t* mz_rudp_manager_new();
MZ_API int mz_rudp_manager_reliable_send(mz_rudp_manager_t *me, mz_rudp_t *sender, char *buf, int sz, mz_rudp_addr_t *dst);
MZ_API int mz_rudp_manager_reliable_recv(mz_rudp_manager_t *me, mz_rudp_t *sender, char *buf, int sz, mz_rudp_addr_t *dst);

#endif
