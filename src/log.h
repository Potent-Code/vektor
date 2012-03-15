/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#ifndef log_h
#define log_h

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

extern void init_log(void);
extern void log_add(const char* str);
extern void log_add_no_eol(const char* str);
#define log_err(a) _log_err(a, __func__, __FILE__, __LINE__)
#define log_err_sys(a) _log_err_sys(a, errno, __func__, __FILE__, __LINE__)
extern void _log_err(const char* str, const char* func, const char* infile, int linenum);
extern void _log_err_sys(const char* str, int error, const char* func, const char* infile, int linenum);
extern char* log_get(void);
extern void log_remove(void* p);

#endif
