#include <mz/mz_path.h>
#include <mz/mz_libs.h>
#include <mz/mz_list.h>
#include <sys/dir.h>
#include <sys/stat.h>

static int IS_DIR(const char* path)
{
    struct stat st;
    lstat(path, &st);
    return S_ISDIR(st.st_mode);
}

MZ_API void mz_path_all_folders(mz_list_t *list, const char *folder_path, int is_recursive)
{
    DIR *pdir;
    char temp[512];
    struct dirent *pdirent;

    pdir = opendir(folder_path);

    if (!pdir) {
        printf("opendir error:%s\n", folder_path);
        closedir(pdir);
    }

    while(NULL != (pdirent = readdir(pdir))) {
        if (mz_strequal(pdirent->d_name, ".") || 
            mz_strequal(pdirent->d_name, ".."))
            continue;

        mz_snprintf(temp, sizeof(temp), "%s/%s", folder_path, pdirent->d_name);

        if(IS_DIR(temp) && is_recursive)
            mz_path_all_folders(list, temp, is_recursive);
        else
            mz_list_add(list, mz_strdup(temp));
    }

    closedir(pdir);

}

MZ_API void mz_path_all_files(mz_list_t *list, const char *folder_path, int is_recursive)
{
    DIR *pdir;
    char temp[512];
    struct dirent *pdirent;

    pdir = opendir(folder_path);

    if (!pdir) {
        printf("opendir error:%s\n", folder_path);
        closedir(pdir);
    }

    while(NULL != (pdirent = readdir(pdir))) {
        if (mz_strequal(pdirent->d_name, ".") || 
            mz_strequal(pdirent->d_name, ".."))
            continue;

        mz_snprintf(temp, sizeof(temp), "%s/%s", folder_path, pdirent->d_name);

        if(IS_DIR(temp) && is_recursive)
            mz_path_all_files(list, temp, is_recursive);
        else
            mz_list_add(list, mz_strdup(temp));
    }

    closedir(pdir);
}
