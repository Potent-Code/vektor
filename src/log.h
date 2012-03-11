/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#ifndef LOG_H
#define LOG_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern void init_log(void);
extern void log_add(const char* str);
extern void log_add_no_eol(const char* str);
extern void log_err(const char* str);
extern void log_err_sys(const char* str, int error);
extern char* log_get(void);
extern void free_log(void);

#endif
