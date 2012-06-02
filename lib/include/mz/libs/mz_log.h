#ifndef __MZ_LOG_H__
#define __MZ_LOG_H__

#include <mz/libs/mz_defs.h>

MZ_API void     mz_print_log(const char *type, const char *format, ...);

#define logI(args...) mz_print_log("Info", args) 
#define logE(args...) mz_print_log("Error", args) 

#endif
