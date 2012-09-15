#include "sl_list.h"

void sl_list_init(sl_list_t* head)
{
    head->next = head;
    head->prev = head;
}

void sl_list_add_tail(sl_list_t* head, sl_list_t* node)
{
    sl_list_t *prev = head->prev; 
    sl_list_t *next = head; 

    next->prev = node; 
    node->next = next;
    node->prev = prev;
    prev->next = node;
}

void sl_list_remove(sl_list_t* node)
{
    sl_list_t *prev = node->prev; 
    sl_list_t *next = node->next; 

    prev->next = next;
    next->prev = prev;

    sl_list_init(node);
}
