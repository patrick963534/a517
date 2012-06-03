#ifndef __MZ_DEFS_H__
#define __MZ_DEFS_H__

#define MZ_API extern
#define mz_unused(arg) (void)(arg)
#define mz_downcast(type) type* me= (type*)me_

#define MZ_TRUE     1
#define MZ_FALSE    0

typedef int         mz_bool;
typedef long long   mz_int64;

#endif
