/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#ifndef LOG_H
#define LOG_H

#include <stdlib.h>

extern void init_log(void);
extern void log_add(char *str);
extern char* log_get(void);
extern void free_log(void);

#endif
