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

static mz_bool create_single_folder(const char *path)
{
    struct stat st;
    mz_bool status = MZ_TRUE;

    if (0 != stat(path, &st))
    {
        /* Directory does not exist */
        if (mkdir(path, 0777) != 0)
            status = MZ_FALSE;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        status = MZ_FALSE;
    }

    return status;
}

MZ_API mz_bool mz_path_create_folder(const char *folder_path, mz_bool is_recursive)
{
    if (!is_recursive) {
        return create_single_folder(folder_path);
    }
    else {
        char *path = mz_strdup(folder_path);
        char *sp = path;
        char *next = sp;
        mz_bool status = MZ_TRUE;
        
        while (status && NULL != (sp = strchr(next, '/'))) {
            if (sp != next) {
                *sp = '\0';
                status = create_single_folder(path);
                *sp = '/';
            }
            next = sp + 1;
        }

        if (status)
            status = create_single_folder(path);

        mz_free(path);

        return status;
    }    
}

MZ_API char* mz_path_get_folder(const char *file_path)
{
    char *p = mz_strdup(file_path);
    char *sp;

    if (NULL != (sp = mz_strrchr(p, '/'))) {
        *sp = '\0';
    }
    else {
        mz_free(p);
        p = mz_strdup("./");
    }
        
    return p;
}

MZ_API void mz_path_all_folders(mz_list_t *list, const char *folder_path, mz_bool is_recursive)
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

MZ_API void mz_path_all_files(mz_list_t *list, const char *folder_path, mz_bool is_recursive)
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
