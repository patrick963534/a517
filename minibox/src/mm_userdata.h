#ifndef __MM_USERDATA_H__
#define __MM_USERDATA_H__

#include <mz/mz_libs.h>
#include <mz/mz_path.h>

typedef struct mm_userdata_t
{
    mz_list_t   *music_files; // DON'T rename its name, because of MACRO stuff.
} mm_userdata_t;

void mm_userdata_init();
mm_userdata_t* mm_userdata_singleton();

void mm_userdata_load(mm_userdata_t *me);
void mm_userdata_save(mm_userdata_t *me);

void mm_userdata_add_file(mm_userdata_t *me, const char *file_path);
void mm_userdata_remove_by_index(mm_userdata_t *me, int index);

#define mm_userdata_music_file_foreach(userdata_, pos_)   \
    mz_list_foreach(userdata_->music_files, pos_, char)
    
static mm_userdata_t *singleton;
static const char *config_file = "~/.minibox/minibox.conf";

void mm_userdata_init()
{
    mm_userdata_t *me = mz_malloc(sizeof(*me));
    me->music_files = mz_list_new();
    
    mm_userdata_load(me);

    singleton = me;
}

mm_userdata_t* mm_userdata_singleton()
{
    return singleton;
}

mz_bool mm_userdata_load(mm_userdata_t *me)
{
    FILE *fp;

    if (NULL == (fp = fopen(file_config, "rt"))) 
        return;


}

mz_bool mm_userdata_save(mm_userdata_t *me);

void mm_userdata_add_file(mm_userdata_t *me, const char *file_path);
void mm_userdata_remove_by_index(mm_userdata_t *me, int index);




#endif
