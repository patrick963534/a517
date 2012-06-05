#ifndef  LEAK_DETECTOR_C_H
#define  LEAK_DETECTOR_C_H

void *  xmalloc(unsigned int size, const char * file, unsigned int line);
void *  xcalloc(unsigned int elements, unsigned int size, const char * file, unsigned int line);
void *  xrealloc(void *src, unsigned int size, const char * file, unsigned int line);
void    xfree(void * mem_ref);
void    report_mem_leak(void);

#endif

