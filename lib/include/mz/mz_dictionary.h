#ifndef __MZ_DICTIONARY_H__
#define __MZ_DICTIONARY_H__

#include <mz/mz_libs.h>
#include <mz/mz_list.h>

typedef struct mz_dictionary_t
{
    mz_list_t   *root;
} mz_dictionary_t;

MZ_API mz_dictionary_t* mz_dictionary_new();
MZ_API void             mz_dictionary_delete(mz_dictionary_t *me);
MZ_API void             mz_dictionary_clear(mz_dictionary_t *me);
MZ_API void             mz_dictionary_add(mz_dictionary_t *me, const char *key, void *value);
MZ_API void             mz_dictionary_remove(mz_dictionary_t *me, const char *key);
MZ_API void*            mz_dictionary_contains(mz_dictionary_t *me, const char *key);

#endif
