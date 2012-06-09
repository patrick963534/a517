#ifndef __YC_PKG_H__
#define __YC_PKG_H__

typedef enum yc_pkg_type_t yc_pkg_type_t;

#define yc_pkg_extends()    \
    int             token;  \
    yc_pkg_type_t   type; \
    int             id

typedef struct yc_pkg_t
{
    yc_pkg_extends();
} yc_pkg_t;

enum yc_pkg_type_t
{

};

#endif
