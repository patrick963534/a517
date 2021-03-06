#include <mz/mz_dictionary.h>
#include <mz/mz_list.h>

typedef struct mz_dictionary_item_t
{
    char          *key;
    void    *value;
} mz_dictionary_item_t;

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
    it->key = mz_strdup(key);
    it->value = value;

    mz_list_add(me->root, it);
}
MZ_API void mz_dictionary_each_do(mz_dictionary_t *me, mz_dictionary_each_do_func func)
{
    mz_dictionary_item_t *it;

    mz_list_foreach(me->root, it, mz_dictionary_item_t) {
        func(it->value);
    }
}

MZ_API void mz_dictionary_clear(mz_dictionary_t *me)
{
    mz_dictionary_item_t *it;

    mz_list_foreach(me->root, it, mz_dictionary_item_t) {
        mz_list_remove(me->root, it);
        mz_free(it->key);
        mz_free(it);
    }
}

MZ_API void* mz_dictionary_contains(mz_dictionary_t *me, const char *key)
{
    mz_dictionary_item_t *it;

    mz_list_foreach(me->root, it, mz_dictionary_item_t) {
        if (mz_strequal(it->key, key))
            return it->value;
    }

    return NULL;
}

MZ_API void mz_dictionary_remove(mz_dictionary_t *me, const char *key)
{
    mz_dictionary_item_t *it;

    mz_list_foreach(me->root, it, mz_dictionary_item_t) {
        if (mz_strequal(it->key, key)) {
            mz_list_remove(me->root, it);
            mz_free(it->key);
            mz_free(it);
            return;
        }
    }
}
