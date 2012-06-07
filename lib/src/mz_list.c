#include <mz/mz_list.h>
#include <mz/mz_general_list.h>
#include <mz/mz_libs.h>

#define create_element(ve, ve_type, t_)           \
        ve_type *ve;                                \
        mz_assert(me->type == t_);                \
        ve = (ve_type*)mz_malloc(sizeof(*ve));      \
        mz_general_list_init(&ve->node);            \
        mz_general_list_add(&ve->node, &me->head)

MZ_API mz_list_t* mz_list_new(mz_list_item_type_t type)
{
    mz_list_t *me = mz_malloc(sizeof(*me));
    me->type = type;

    mz_general_list_init(&me->head);

    return me;
}

MZ_API void mz_list_add_int(mz_list_t *me, int v)
{
    create_element(ve, mz_list_item_int_t, mz_list_item_type_int);
    ve->int_value = v;
}

MZ_API void mz_list_add_string(mz_list_t *me, const char *v)
{
    create_element(ve, mz_list_item_string_t, mz_list_item_type_string);
    ve->str_value = mz_string_dup(v);
}

MZ_API void mz_list_add_ptr_ref(mz_list_t *me, void *v)
{
    create_element(ve, mz_list_item_ptr_ref_t, mz_list_item_type_ptr_ref);
    ve->ptr_ref = v;
}

MZ_API int mz_list_position(mz_list_t *me, mz_list_item_t *v)
{
    int i = 0;
    mz_general_list_t *pos;

    mz_general_list_for_each(pos, &me->head) {
        if (pos == &v->node) 
            return i;
        i++;
    }

    return -1;
}

MZ_API void mz_list_remove(mz_list_t *me, mz_list_item_t *v)
{
    mz_general_list_remove(&v->node);

    if (me->type == mz_list_item_type_string) 
        mz_free(((mz_list_item_string_t*)v)->str_value);

    mz_free(v);
}

MZ_API mz_list_item_t* mz_list_index(mz_list_t *me, int index)
{
    int i = 0;
    mz_general_list_t *pos;

    mz_general_list_for_each(pos, &me->head) {
        if (i == index) 
            break;
        i++;
    }

    if (pos == &me->head)
        return NULL;

    return mz_list_entry(pos, mz_list_item_t);
}

MZ_API int mz_list_count(mz_list_t *me)
{
    int i = 0;
    mz_general_list_t *pos;

    mz_general_list_for_each(pos, &me->head) {
        i++;
    }

    return i;
}

MZ_API void mz_list_delete(mz_list_t *me)
{
    mz_list_item_t *pos, *next_pos;
        
    mz_list_for_each_entry_safe(pos, next_pos, me, mz_list_item_t) {
        mz_list_remove(me, pos);
    }

    mz_free(me);
}

MZ_API void mz_list_force_delete_all_ptr_ref(mz_list_t *me)
{
    mz_list_item_ptr_ref_t *pos;

    mz_list_for_each_entry(pos, me, mz_list_item_ptr_ref_t) {
        mz_free(pos->ptr_ref);
    }
}
