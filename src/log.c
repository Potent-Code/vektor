/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#include "log.h"

char *log_data;
unsigned int log_size;

void init_log(void);
void log_add(const char* str);
void log_add_no_eol(const char* str);
void log_err(const char* str);
void log_err_sys(const char* str, int error);
char* log_get(void);
void log_remove(void* p);

void init_log(void)
{
	log_data = calloc(500000,1);
	log_size = 0;
	log_add("Starting Vektor Engine");
}

void log_add(const char* str)
{
	log_add_no_eol(str);
	strncat(log_data, "\n", 1);
	log_size++;
}

void log_add_no_eol(const char* str)
{
	int len;
	if((len = strlen(str) + log_size) < 500000)
	{
		if(len > 0)
		{
			strncat(log_data, str, len);
		}
	}
	log_size += len;
}

void log_err(const char* str)
{
	char error_loc[256];
	snprintf(error_loc, 255, " %s:%d - ", __FILE__, __LINE__);
	log_add_no_eol("ERROR: in ");
	log_add_no_eol(__func__);
	log_add_no_eol(error_loc);
	log_add(str);
	fprintf(stderr, "ERROR: %s\n", str);
}

void log_err_sys(const char* str, int error)
{
	char error_loc[256];
	snprintf(error_loc, 255, " %s:%d - ", __FILE__, __LINE__);
	log_add_no_eol("ERROR: in ");
	log_add_no_eol(__func__);
	log_add_no_eol(error_loc);
	log_add_no_eol(str);
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
	FILE* fd;

	// write log file to disk
	if ((fd = fopen("vektor.log", "w")) != 0)
	{
		fprintf(fd, "%s", log_get());
		fclose(fd);
	}

	free(log_data);
}
