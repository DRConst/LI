#pragma once
#ifndef MALLOC_WRAPPER
#define MALLOC_WRAPPER
#include <stdlib.h>
void* wrp_malloc(size_t sz, const char* file, int line);
void wrp_free(void* ptr, const char* file, int line);
void wrp_mem_report();
void wrp_mem_report_file(char* file);
void wrp_init();
//
// wrap malloc and free
#define malloc(sz) wrp_malloc(sz, __FILE__, __LINE__)
#define free(sz) wrp_free(sz, __FILE__, __LINE__)
#endif

