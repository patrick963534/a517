#ifndef __MZ_LIST_H__
#define __MZ_LIST_H__

#include <mz/libs/mz_defs.h>

typedef struct mz_list_s mz_list_t;

struct mz_list_s {
    mz_list_t *next, *prev;
};

MZ_API void         mz_list_init(mz_list_t *me);
MZ_API void         mz_list_add(mz_list_t *new, mz_list_t *head);
MZ_API void         mz_list_remove(mz_list_t *entry);
MZ_API void         mz_list_replace(mz_list_t *old, mz_list_t *new);
MZ_API void         mz_list_delete(mz_list_t *me);

/**
* mz_list_entry - get the struct for this entry
* @ptr: the &mz_list_t pointer.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the mz_list_struct within the struct.
*/
#define mz_list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
* mz_list_first_entry - get the first element from a list
* @ptr: the list head to take the element from.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the mz_list_struct within the struct.
*
* Note, that list is expected to be not empty.
*/
#define mz_list_first_entry(ptr, type, member) \
    mz_list_entry((ptr)->next, type, member)


#define mz_list_last_entry(ptr, type, member) \
    mz_list_entry((ptr)->prev, type, member)

/**
* mz_list_for_each -   iterate over a list
* @pos: the &mz_list_t to use as a loop cursor.
* @head:    the head for your list.
*/
#define mz_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
* mz_list_for_each_prev    -   iterate over a list backwards
* @pos: the &mz_list_t to use as a loop cursor.
* @head:    the head for your list.
*/
#define mz_list_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
* mz_list_for_each_safe - iterate over a list safe against removal of list entry
* @pos: the &mz_list_t to use as a loop cursor.
* @n:       another &mz_list_t to use as temporary storage
* @head:    the head for your list.
*/
#define mz_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

/**
* mz_list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
* @pos: the &mz_list_t to use as a loop cursor.
* @n:       another &mz_list_t to use as temporary storage
* @head:    the head for your list.
*/
#define mz_list_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; \
    pos != (head); \
    pos = n, n = pos->prev)

/**
* mz_list_for_each_entry   -   iterate over list of given type
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the mz_list_struct within the struct.
*/
#define mz_list_for_each_entry(pos, head, type, member)    \
    for (pos = mz_list_entry((head)->next, type, member);  \
    &pos->member != (head);     \
    pos = mz_list_entry(pos->member.next, type, member))

/**
* mz_list_for_each_entry_reverse - iterate backwards over list of given type.
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @member:  the name of the mz_list_struct within the struct.
*/
#define mz_list_for_each_entry_reverse(pos, head, type, member)            \
    for (pos = mz_list_entry((head)->prev, type, member);  \
    &pos->member != (head);     \
    pos = mz_list_entry(pos->member.prev, type, member))

/**
* mz_list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
* @pos: the type * to use as a loop cursor.
* @n:       another type * to use as temporary storage
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the mz_list_struct within the struct.
*/
#define mz_list_for_each_entry_safe(pos, n, head, type, member)            \
    for (pos = mz_list_entry((head)->next, type, member),  \
    n = mz_list_entry(pos->member.next, type, member); \
    &pos->member != (head);                     \
    pos = n, n = mz_list_entry(n->member.next, type, member))

#endif
