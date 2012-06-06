#include <mz/mz_list.h>
#include <mz/mz_general_list.h>
#include <mz/mz_libs.h>

#define create_element(ve, ve_type, t_)           \
        ve_type *ve;                                \
        mz_assert(me->type == t_);                \
        ve = (ve_type*)mz_malloc(sizeof(*ve));      \
        mz_general_list_init(&ve->node);            \
        mz_general_list_add(&ve->node, &me->head)

MZ_API mz_list_t*  mz_list_new(mz_list_element_type_t type)
{
    mz_list_t *me = mz_malloc(sizeof(*me));
    me->type = type;

    mz_general_list_init(&me->head);

    return me;
}

MZ_API void mz_list_add_int(mz_list_t *me, int v)
{
    create_element(ve, mz_list_element_int_t, mz_list_element_type_int);
    ve->int_value = v;
}

MZ_API void mz_list_add_string(mz_list_t *me, const char *v)
{
    create_element(ve, mz_list_element_string_t, mz_list_element_type_string);
    ve->str_value = mz_string_dup(v);
}

MZ_API void mz_list_add_ptr_ref(mz_list_t *me, void *v)
{
    create_element(ve, mz_list_element_ptr_ref_t, mz_list_element_type_ptr_ref);
    ve->ptr_ref = v;
}
