#ifndef __MZ_FILE_TEXT_H__
#define __MZ_FILE_TEXT_H__ 

#include <mz/mz_libs.h>

typedef struct mz_file_text_t
{
    void *fp;
} mz_file_text_t;

mz_file_text_t* mz_file_text_new(mz_string_t *filepath);
void mz_file_text_delete(mz_file_text_t *me);

void            mz_file_text_write(mm_file_text_t *me, mz_string_t *text);
mz_string_t*    mz_file_text_read_line(mm_file_text_t *me);

#endif
