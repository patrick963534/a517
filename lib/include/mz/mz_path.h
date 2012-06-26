#ifndef __MZ_PATH_H__
#define __MZ_PATH_H__

#include <mz/mz_libs.h>
#include <mz/mz_list.h>

/*
 * Usage: mz_path_create_folder("res/a/b/c", MZ_TRUE);
 */
MZ_API mz_bool  mz_path_create_folder(const char *folder_path, mz_bool is_recursive);

MZ_API char*    mz_path_get_folder(const char *file_path);

MZ_API void     mz_path_all_folders(mz_list_t *list, const char *folder_path, mz_bool is_recursive);
MZ_API void     mz_path_all_files(mz_list_t *list, const char *folder_path, mz_bool is_recursive);

#endif
