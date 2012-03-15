/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#include "log.h"

char* log_data = NULL;
unsigned int log_size = 0;

FILE* log_fd = NULL;

void init_log(void);
void log_add(const char* str);
void log_add_no_eol(const char* str);
void _log_err(const char* str, const char* func, const char* infile, int linenum);
void _log_err_sys(const char* str, int error, const char* func, const char* infile, int linenum);
char* log_get(void);
void log_remove(void* p);

void init_log(void)
{
	if (log_data == NULL)
	{
		log_data = calloc(500000, 1);
		#ifndef VEKTOR_NO_LOG
		log_fd = fopen("vektor.log", "w");
		#endif
		log_add("Starting Vektor Engine");
		log_size = strlen(log_data);
	} else {
		fprintf(stderr, "Log already initialized");
	}
}

void log_add(const char* str)
{
	if (log_data == NULL)
	{
		fprintf(stderr, "Log not initialized");
		return;
	}
	log_add_no_eol(str);
	strncat(log_data, "\n", 1);
	#ifndef VEKTOR_NO_LOG
	fprintf(log_fd, "\n");
	#endif
	log_size++;
}

void log_add_no_eol(const char* str)
{
	const unsigned int len = strlen(str);

	if (log_data == NULL)
	{
		fprintf(stderr, "Log not initialized");
		return;
	}

	if ((len + log_size) < 500000)
	{
		if(len > 0)
		{
			strncat(log_data, str, len);
			#ifndef VEKTOR_NO_LOG
			fprintf(log_fd, "%s", str);
			#endif
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
	#ifndef VEKTOR_NO_LOG
	if (fflush(log_fd) != 0)
	{
		perror("Error writing log file");
	}
	fclose(log_fd);
	#endif

	free(log_data);
}
