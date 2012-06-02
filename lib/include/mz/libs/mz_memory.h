#ifndef __MZ_MEMORY_H__
#define __MZ_MEMORY_H__

#include <malloc.h>
#include <string.h>

#define mz_memcpy(dst, src, size) memcpy(dst, src, size)
#define mz_malloc(size) calloc(1, size)
#define mz_realloc(ptr, size) realloc(ptr, size)
#define mz_free(obj) free(obj)
#define mz_memset(dst, v, sz) memset(dst, v, sz)

#endif
