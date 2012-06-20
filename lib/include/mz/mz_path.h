#ifndef __MZ_PATH_H__
#define __MZ_PATH_H__

#include <mz/mz_libs.h>
#include <mz/mz_list.h>

MZ_API void mz_path_all_files(mz_list_t *list, const char *folder_path, int is_recursive);

#endif
