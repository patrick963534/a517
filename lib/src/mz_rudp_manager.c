#include <mz/mz_rudp_manager.h>
#include <mz/mz_libs.h>

MZ_API mz_rudp_manager_t* mz_rudp_manager_new()
{
    mz_rudp_manager_t *me = mz_malloc(sizeof(*me));

    return me;
}

MZ_API int mz_rudp_manager_reliable_send(mz_rudp_manager_t *me, mz_rudp_t *sender, char *buf, int sz, mz_rudp_addr_t *dst)
{
    return 0;
}

MZ_API int mz_rudp_manager_reliable_recv(mz_rudp_manager_t *me, mz_rudp_t *sender, char *buf, int sz, mz_rudp_addr_t *dst)
{
    return 0;
}
