#ifndef __SL_LIST_H__
#define __SL_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sl_list_t
{
    struct sl_list_t* prev;
    struct sl_list_t* next;
} sl_list_t;

void sl_list_init(sl_list_t* head);
void sl_list_add_tail(sl_list_t* head, sl_list_t* node);
void sl_list_remove(sl_list_t* node);
void sl_list_insert_after(sl_list_t* pos, sl_list_t* node);
void sl_list_insert_before(sl_list_t* pos, sl_list_t* node);

#define sl_list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define sl_list_empty(head) \
    ((head)->next == (head))

#define sl_list_next_entry(ptr, type, member) \
    sl_list_entry((ptr)->member.next, type, member)

#define sl_list_first_entry(head, type, member) \
    sl_list_entry((head)->next, type, member)

#define sl_list_last_entry(head, type, member) \
    sl_list_entry((head)->prev, type, member)

/*
 @pos:      each item to pointer of @type.
 @head:     sl_list_t*
 @type:     type of @pos
 @member:   name of sl_list_t in the @type structure.
*/
#define sl_list_for_each_entry(pos, head, type, member)            \
    for (pos = sl_list_entry((head)->prev, type, member);  \
         &pos->member != (head);     \
          pos = sl_list_entry(pos->member.prev, type, member))

#define sl_list_for_each_entry_safe(pos, n, head, type, member)            \
    for (pos = sl_list_entry((head)->next, type, member),  \
          n = sl_list_entry(pos->member.next, type, member); \
         &pos->member != (head);                     \
          pos = n, n = sl_list_entry(n->member.next, type, member))



#ifdef __cplusplus
}
#endif

#endif
