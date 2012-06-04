#ifndef __MZ_MEMORY_H__
#define __MZ_MEMORY_H__

#include <mz/libs/mz_defs.h>
#include <malloc.h>
#include <string.h>

MZ_API void* mz_malloc_(unsigned int size, const char * file, unsigned int line);
MZ_API void* mz_calloc_(int element, unsigned int size, const char * file, unsigned int line);
MZ_API void* mz_realloc_(void *ptr, unsigned int size, const char * file, unsigned int line);
MZ_API void  mz_free(void *ptr);
MZ_API void  mz_print_memory_log();

#define mz_memcpy(dst, src, size)   memcpy(dst, src, size)
#define mz_memset(dst, v, sz)       memset(dst, v, sz)
#define mz_malloc(size)             mz_calloc_(1, size, __FILE__, __LINE__)
#define mz_calloc(element, size)    mz_calloc_(element, size, __FILE__, __LINE__)
#define mz_realloc(ptr, size)       mz_realloc_(ptr, size, __FILE__, __LINE__)

#endif
