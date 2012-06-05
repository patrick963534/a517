#ifndef __MZ_LIST_H__
#define __MZ_LIST_H__

#include <mz/libs/mz_defs.h>

typedef struct list_s list_t;

struct list_s {
    list_t *next, *prev;
};


MZ_API void INIT_LIST_HEAD(list_t *list);
MZ_API void list_add(list_t *_new, list_t *head);
MZ_API void list_add_tail(list_t *_new, list_t *head);
MZ_API void list_del(list_t *entry);
MZ_API void list_replace(list_t *old, list_t *_new);

#endif
