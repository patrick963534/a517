#include <mz/mz_dictionary.h>

typedef struct mz_dictionary_item_t
{
    char          *key;
    const void    *value;
} mz_directory_item_t;

MZ_API mz_dictionary_t* mz_dictionary_new()
{
    mz_dictionary_t *me = mz_malloc(sizeof(*me));
    me->root = mz_list_new();

    return me;
}

MZ_API void mz_dictionary_delete(mz_dictionary_t *me)
{
    mz_dictionary_clear(me);
    mz_list_delete(me->root);
    mz_free(me);
}

MZ_API void mz_dictionary_add(mz_dictionary_t *me, const char *key, void *value)
{
    mz_dictionary_item_t *it = mz_malloc(sizeof(*it));
    it->key = mz_string_dup(key);
    it->value = value;

    mz_list_add(me->root, it);
}

MZ_API void mz_dictionary_clear(mz_dictionary_t *me)
{
    mz_list_clear(me->root);
}