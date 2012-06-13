#ifndef __MZ_HASH_TABLE_H__
#define __MZ_HASH_TABLE_H__

#include <mz/libs/mz_defs.h>

typedef struct mz_hash_table_t
{

} mz_hash_table_t;

MZ_API mz_hash_table_t* mz_hash_table_new();
MZ_API void             mz_hash_table_delete(mz_hash_table_t *me);

MZ_API void             mz_hash_table_add_int_key(mz_hash_table_t *me, int key, void *value);
MZ_API void             mz_hash_table_add_string_key(mz_hash_table_t *me, const char *key, void *value);
MZ_API void             mz_hash_table_remove_int_key(mz_hash_table_t *me, int key);
MZ_API void             mz_hash_table_remove_string_key(mz_hash_table_t *me, const char *key);
MZ_API void*            mz_hash_table_get_item_int_key(mz_hash_table_t *me, int key);
MZ_API void*            mz_hash_table_get_item_string_key(mz_hash_table_t *me, const char *key);

#endif
