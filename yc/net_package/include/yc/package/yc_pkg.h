#ifndef __YC_PKG_H__
#define __YC_PKG_H__

typedef enum yc_pkg_type_t
{
    yc_pkg_type_connect,
    yc_pkg_type_connect_result,

    yc_pkg_type_chat_single,
    yc_pkg_type_chat_single_result,

    yc_pkg_type_max_value = 64
} yc_pkg_type_t;

#define yc_pkg_extends()    \
    int             token;  \
    yc_pkg_type_t   type; \
    int             id

typedef struct yc_pkg_t
{
    yc_pkg_extends();
} yc_pkg_t;

#endif
