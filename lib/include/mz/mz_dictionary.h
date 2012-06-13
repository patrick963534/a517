#ifndef __MZ_DICTIONARY_H__
#define __MZ_DICTIONARY_H__

#include <mz/libs/mz_defs.h>

typedef struct mz_dictionary_t
{

} mz_dictionary_t;

MZ_API mz_dictionary_t* mz_dictionary_new();
MZ_API void             mz_dictionary_delete(mz_dictionary_t *me);

MZ_API void             mz_dictionary_add_int_key(mz_dictionary_t *me, int key, void *value);
MZ_API void             mz_dictionary_add(mz_dictionary_t *me, const char *key, void *value);
MZ_API void             mz_dictionary_remove_int_key(mz_dictionary_t *me, int key);
MZ_API void             mz_dictionary_remove(mz_dictionary_t *me, const char *key);
MZ_API void*            mz_dictionary_contains_int_key(mz_dictionary_t *me, int key);
MZ_API void*            mz_dictionary_contains(mz_dictionary_t *me, const char *key);

#endif
