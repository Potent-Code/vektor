/* engine log
 * by Ryan Lucchese
 * July 30 2011 */

#include "log.h"

char *log_data;
unsigned int log_size;

void init_log(void);
void log_add(char* str);
void log_add_no_eol(char* str);
char* log_get(void);
void free_log(void);

void init_log(void)
{
	int i;
	char str[256];
	log_data = calloc(500000,1);
	log_size = 0;
	log_add("Starting Vektor Engine");
	/*for(i = 0; i < 150; i++)
	{
		snprintf(&str[0], 4, "%d", i);
		log_add(&str[0]);
	}*/
}

void log_add(char* str)
{
	int len;
	if((len = strlen(str) + log_size) < 500000)
	{
		if(len > 0)
		{
			strncat(log_data,str,len);
		}
	}
	strncat(log_data,"\n",1);
	log_size = strlen(log_data);
}

void log_add_no_eol(char* str)
{
	int len;
	if((len = strlen(str) + log_size) < 500000)
	{
		if(len > 0)
		{
			strncat(log_data,str,len);
		}
	}
	log_size = strlen(log_data);
}

char* log_get(void)
{
	return log_data;
}

void free_log(void)
{
	free(log_data);
}
