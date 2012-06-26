#ifndef __MZ_FILE_TEXT_H__
#define __MZ_FILE_TEXT_H__ 

typedef struct mz_file_text_t
{
    void *fp;
} mz_file_text_t;

mz_file_text_t* mz_file_text_new(const char *filepath);
void mz_file_text_delete(mz_file_text_t *me);

#endif
