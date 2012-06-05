#include <mz/mz_list.h>
#include <mz/libs/mz_defs.h>

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    list_t name = LIST_HEAD_INIT(name)

MZ_API void INIT_LIST_HEAD(list_t *list)
{
    list->next = list;
    list->prev = list;
}

static __inline void __list_add(list_t *_new, list_t *prev, list_t *next)
{
    next->prev = _new;
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
}

MZ_API void list_add(list_t *_new, list_t *head)
{
    __list_add(_new, head, head->next);
}

MZ_API void list_add_tail(list_t *_new, list_t *head)
{
    __list_add(_new, head->prev, head);
}

static __inline void __list_del(list_t * prev, list_t * next)
{
    next->prev = prev;
    prev->next = next;
}

MZ_API void list_del(list_t *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = (list_t *) 0;
    entry->prev = (list_t *) 0;
}

MZ_API void list_replace(list_t *old, list_t *_new)
{
    _new->next = old->next;
    _new->next->prev = _new;
    _new->prev = old->prev;
    _new->prev->next = _new;
}

/**
* list_entry - get the struct for this entry
* @ptr: the &list_t pointer.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*/
#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
* list_first_entry - get the first element from a list
* @ptr: the list head to take the element from.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Note, that list is expected to be not empty.
*/
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)


#define list_last_entry(ptr, type, member) \
    list_entry((ptr)->prev, type, member)

/**
* list_for_each -   iterate over a list
* @pos: the &list_t to use as a loop cursor.
* @head:    the head for your list.
*/
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
* list_for_each_prev    -   iterate over a list backwards
* @pos: the &list_t to use as a loop cursor.
* @head:    the head for your list.
*/
#define list_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
* list_for_each_safe - iterate over a list safe against removal of list entry
* @pos: the &list_t to use as a loop cursor.
* @n:       another &list_t to use as temporary storage
* @head:    the head for your list.
*/
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

/**
* list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
* @pos: the &list_t to use as a loop cursor.
* @n:       another &list_t to use as temporary storage
* @head:    the head for your list.
*/
#define list_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; \
    pos != (head); \
    pos = n, n = pos->prev)

/**
* list_for_each_entry   -   iterate over list of given type
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*/
#define list_for_each_entry(pos, head, type, member)    \
    for (pos = list_entry((head)->next, type, member);  \
    &pos->member != (head);     \
    pos = list_entry(pos->member.next, type, member))

/**
* list_for_each_entry_reverse - iterate backwards over list of given type.
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @member:  the name of the list_struct within the struct.
*/
#define list_for_each_entry_reverse(pos, head, type, member)            \
    for (pos = list_entry((head)->prev, type, member);  \
    &pos->member != (head);     \
    pos = list_entry(pos->member.prev, type, member))

/**
* list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue()
* @pos: the type * to use as a start point
* @head:    the head of the list
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Prepares a pos entry for use as a start point in list_for_each_entry_continue().
*/
#define list_prepare_entry(pos, head, type, member) \
    ((pos) ? list_entry(head, type, member) : NULL)

/**
* list_for_each_entry_continue - continue iteration over list of given type
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Continue to iterate over list of given type, continuing after
* the current position.
*/
#define list_for_each_entry_continue(pos, head, type, member)       \
    for (pos = list_entry(pos->member.next, type, member);  \
    &pos->member != (head); \
    pos = list_entry(pos->member.next, type, member))

/**
* list_for_each_entry_continue_reverse - iterate backwards from the given point
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Start to iterate over list of given type backwards, continuing after
* the current position.
*/
#define list_for_each_entry_continue_reverse(pos, head, type, member)       \
    for (pos = list_entry(pos->member.prev, type, member); \
    &pos->member != (head); \
    pos = list_entry(pos->member.prev, type, member))

/**
* list_for_each_entry_from - iterate over list of given type from the current point
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Iterate over list of given type, continuing from current position.
*/
#define list_for_each_entry_from(pos, head, type, member)           \
    for (;&pos->member != (head); pos = list_entry(pos->member.next, type, member))

/**
* list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
* @pos: the type * to use as a loop cursor.
* @n:       another type * to use as temporary storage
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*/
#define list_for_each_entry_safe(pos, n, head, type, member)            \
    for (pos = list_entry((head)->next, type, member),  \
    n = list_entry(pos->member.next, type, member); \
    &pos->member != (head);                     \
    pos = n, n = list_entry(n->member.next, type, member))

/**
* list_for_each_entry_safe_continue
* @pos: the type * to use as a loop cursor.
* @n:       another type * to use as temporary storage
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Iterate over list of given type, continuing after current point,
* safe against removal of list entry.
*/
#define list_for_each_entry_safe_continue(pos, n, head, type, member)       \
    for (pos = list_entry(pos->member.next, type, member),      \
    n = list_entry(pos->member.next, type, member);     \
    &pos->member != (head);                     \
    pos = n, n = list_entry(n->member.next, type, member))

/**
* list_for_each_entry_safe_from
* @pos: the type * to use as a loop cursor.
* @n:       another type * to use as temporary storage
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Iterate over list of given type from current point, safe against
* removal of list entry.
*/
#define list_for_each_entry_safe_from(pos, n, head, type, member)           \
    for (n = list_entry(pos->member.next, type, member);        \
    &pos->member != (head);                     \
    pos = n, n = list_entry(n->member.next, type, member))

/**
* list_for_each_entry_safe_reverse
* @pos: the type * to use as a loop cursor.
* @n:       another type * to use as temporary storage
* @head:    the head for your list.
* @type:    the type of the struct this is embedded in.
* @member:  the name of the list_struct within the struct.
*
* Iterate backwards over list of given type, safe against removal
* of list entry.
*/
#define list_for_each_entry_safe_reverse(pos, n, head, type, member)        \
    for (pos = list_entry((head)->prev, type, member),  \
    n = list_entry(pos->member.prev, type, member); \
    &pos->member != (head);                     \
    pos = n, n = list_entry(n->member.prev, type, member))


