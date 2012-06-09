#ifndef __YC_PKG_H__
#define __YC_PKG_H__

#include <mz/libs/mz_list.h>
#include <mz/libs/mz_libs.h>

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
    yc_pkg_type_test_check_connect = 0;

    yc_pkg_type_max_value = 64;
};

typedef struct yc_pkg_test_check_connect_t
{
    yc_pkg_extends();
} yc_pkg_test_check_connect_t;

typedef void (*yz_pkg_process_func)(...);

typedef struct yc_pkg_processor_t
{
    yc_pkg_type_t           type;
    yz_pkg_process_func     processor;

} yc_pkg_processor_t;

#define yc_pkg_add_processor(list, type_name)  \
    {   \
        yc_pkg_processor_t *pkg = mz_malloc(sizeof(*pkg));  \
        pkg->type = yc_pkg_type_ ## type_name;   \
        pkg->processor = yc_pkg_ ## type_name ## _processor;    \
        mz_list_add_ptr_ref(list, pkg); \
    }

void init_package_processors()
{
    mz_list_t *list;
    yc_pkg_add_processor(list, test_check_connect);
}

#endif
