#ifndef __MZ_LIST_H__
#define __MZ_LIST_H__

#include <mz/libs/mz_defs.h>
#include <mz/mz_general_list.h>

typedef enum mz_list_element_type_t
{
    mz_list_element_type_int,
    mz_list_element_type_string,
    mz_list_element_type_bytes,
    mz_list_element_type_ptr_ref
} mz_list_element_type_t;

#define mz_extends_list_element()           \
            mz_general_list_t       node

typedef struct mz_list_element_int_t
{
    mz_extends_list_element();
    int int_value;
} mz_list_element_int_t;

typedef struct mz_list_element_string_t
{
    mz_extends_list_element();
    char *str_value;
} mz_list_element_string_t;

typedef struct mz_list_element_ptr_ref_t
{
    mz_extends_list_element();
    void *ptr_ref;
} mz_list_element_ptr_ref_t;

typedef struct mz_list_t
{
    mz_list_element_type_t  type;
    mz_general_list_t       head;
} mz_list_t;

MZ_API mz_list_t*  mz_list_new(mz_list_element_type_t type);
MZ_API void        mz_list_delete(mz_list_t *me);
MZ_API void        mz_list_add_int(mz_list_t *me, int v);
MZ_API void        mz_list_add_string(mz_list_t *me, const char *v);
MZ_API void        mz_list_add_ptr_ref(mz_list_t *me, void *v);

#define mz_list_entry(ptr, type) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->node)))

#define mz_list_for_each(pos, head)   \
            for (pos = (head)->next; pos != head; pos = pos->next)

#define mz_list_for_each_entry(pos, head, type)    \
    for (pos = mz_list_entry((head)->next, type);  \
        &pos->node != (head);     \
         pos = mz_list_entry(pos->node.next, type))

#endif
