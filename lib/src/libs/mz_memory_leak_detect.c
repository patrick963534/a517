#include    "mz_memory_leak_detect.h"
#include    <stdio.h>
#include    <malloc.h>
#include    <string.h>

#define  FILE_NAME_LENGTH          256

struct _mem_info_t
{
    void            *address;
    unsigned int    size;
    char            file_name[FILE_NAME_LENGTH];
    unsigned int    line;
};
typedef struct _mem_info_t mem_info_t;

struct _mem_leak_t {
    mem_info_t mem_info;
    struct _mem_leak_t * next;
};
typedef struct _mem_leak_t mem_leak_t;

static mem_leak_t *ptr_start = NULL;

static void list_add(mem_info_t *info)
{
    mem_leak_t * link = (mem_leak_t*)malloc(sizeof(*link));

    link->mem_info.address = info->address;
    link->mem_info.size = info->size;
    link->mem_info.line = info->line;
    link->next = NULL;

    strcpy(link->mem_info.file_name, info->file_name); 

    if (ptr_start != NULL) 
        link->next = ptr_start;

    ptr_start = link;
}

static void list_erase(unsigned pos)
{
    mem_leak_t *temp;

    if(pos == 0) {
        temp = ptr_start;
        ptr_start = ptr_start->next;
        free(temp);
    }
    else {
        unsigned index = 0;
        mem_leak_t *link = ptr_start;

        for(; index < pos; link = link->next, ++index) {
            if(pos == index + 1) {
                temp = link->next;
                link->next = temp->next;
                free(temp);
                break;
            }
        }
    }
}

static void list_clear()
{
    mem_leak_t *temp = ptr_start;
    mem_leak_t *link = ptr_start;

    while(link != NULL) {
        link = link->next;
        free(temp);
        temp = link;
    }
}

static void add_mem_info (void * mem_ref, unsigned int size,  const char * file, unsigned int line)
{
    mem_info_t info;

    info.address = mem_ref;
    info.size = size;
    info.line = line;
    strncpy(info.file_name, file, FILE_NAME_LENGTH);
    
    list_add(&info);
}

static void remove_mem_info(void * mem_ref)
{
    unsigned index;
    mem_leak_t *leak_info = ptr_start;

    for(index = 0; leak_info != NULL; ++index, leak_info = leak_info->next) {
        if (leak_info->mem_info.address == mem_ref) {
            list_erase(index);
            break;
        }
    }
}

void * xmalloc (unsigned int size, const char * file, unsigned int line)
{
    void * ptr = malloc (size);

    if (ptr != NULL) 
        add_mem_info(ptr, size, file, line);

    return ptr;
}

void * xcalloc (unsigned int elements, unsigned int size, const char * file, unsigned int line)
{
    void * ptr = calloc(elements , size);

    if(ptr != NULL)
        add_mem_info(ptr, elements * size, file, line);

    return ptr;
}

void * xrealloc(void *src, unsigned int size, const char * file, unsigned int line)
{
    void * ptr;

    remove_mem_info(src);
    ptr = realloc(src, size);

    if (ptr != NULL) 
        add_mem_info(ptr, size, file, line);

    return ptr;
}

void xfree(void * mem_ref)
{
    remove_mem_info(mem_ref);
    free(mem_ref);
}

void report_mem_leak(void)
{
    unsigned short index;
    mem_leak_t * leak_info;

    printf("%s\n", "-----------------------------------");
    printf("%s\n", "Memory Leak Summary");
    printf("%s\n", "-----------------------------------");

    if (ptr_start == NULL) {
        printf("NO memory leak detected.\n");
    } 
    else {
        for(leak_info = ptr_start; leak_info != NULL; leak_info = leak_info->next)
        {
            printf("address : %d\n", leak_info->mem_info.address);
            printf("size    : %d bytes\n", leak_info->mem_info.size);            
            printf("file    : %s\n", leak_info->mem_info.file_name);
            printf("line    : %d\n", leak_info->mem_info.line);
            printf("%s\n", "-----------------------------------");   
        }
    }

    fflush(stdout);

    list_clear();
}

