/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#include "log.h"

char *log_data;
unsigned int log_size;

FILE* log_fd;

void init_log(void);
void log_add(const char* str);
void log_add_no_eol(const char* str);
void _log_err(const char* str, const char* func, const char* infile, int linenum);
void _log_err_sys(const char* str, int error, const char* func, const char* infile, int linenum);
char* log_get(void);
void log_remove(void* p);

void init_log(void)
{
	log_data = calloc(500000,1);
	log_size = 0;
	log_fd = fopen("vektor.log", "w");
	log_add("Starting Vektor Engine");
}

void log_add(const char* str)
{
	log_add_no_eol(str);
	strncat(log_data, "\n", 1);
	fprintf(log_fd, "\n");
	log_size++;
}

void log_add_no_eol(const char* str)
{
	int len = 0;

	if((len = strlen(str) + log_size) < 500000)
	{
		if(len > 0)
		{
			strncat(log_data, str, len);
			fprintf(log_fd, "%s", str);
			log_size += len;
		}
	}
}

void _log_err(const char* str, const char* func, const char* infile, int linenum)
{
	char error_loc[256];
	snprintf(error_loc, 255, "() %s:%d - ", infile, linenum);
	log_add_no_eol("** ERROR: in ");
	log_add_no_eol(func);
	log_add_no_eol(error_loc);
	log_add(str);
	fprintf(stderr, "ERROR: %s\n", str);
}

void _log_err_sys(const char* str, int error, const char* func, const char* infile, int linenum)
{
	char error_loc[256];
	snprintf(error_loc, 255, "() %s:%d - ", infile, linenum);
	log_add_no_eol("** ERROR: in ");
	log_add_no_eol(func);
	log_add_no_eol(error_loc);
	log_add_no_eol(str);
	log_add_no_eol(": ");
	log_add(strerror(error));
	fprintf(stderr, "ERROR: %s: %s\n", str, strerror(error));
}

char* log_get(void)
{
	return log_data;
}

void log_remove(void* p)
{
	(void)p;

	// close the log file
	fclose(log_fd);

	free(log_data);
}
