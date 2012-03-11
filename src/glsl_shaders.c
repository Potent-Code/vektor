/* GLSL Shaders
 * by Ryan Lucchese
 * January 9 2012 */

#include "glsl_shaders.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void vertex_shader_install(const char* filename);
void fragment_shader_install(const char* filename);
char* shader_load(const char* filename);
int shader_attach(int id, const char* filename);
void shader_init();
void shader_remove(void* p);

int gl_vertex_shader = 0;
int gl_fragment_shader = 0;
int shader_program = 0;

int in_pos_attrib = 0;
int in_color_attrib = 0;

void vertex_shader_install(const char* filename)
{
	gl_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	shader_attach(gl_vertex_shader, filename);
}

void fragment_shader_install(const char* filename)
{
	gl_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	shader_attach(gl_fragment_shader, filename);
}

char* shader_load(const char* filename)
{
	FILE* fd;
	char* source;
	struct stat filestat;
	int source_len = 0;
	int bytes_read = 0;

	if((fd = fopen(filename, "rb")) == 0)
	{
		perror("Error opening shader file");
		return NULL;
	}

	stat(filename, &filestat);
	source_len = filestat.st_size;

	if((source = calloc(source_len, 1)) == NULL)
	{
		perror("Error allocating memory");
		return NULL;
	}

	bytes_read = fread(source, 1, source_len, fd);
	if (bytes_read != source_len)
	{
		perror("File content length does not match read bytes");
		free(source);
		return NULL;
	}

	fclose(fd);

	return source;
}

int shader_attach(int id, const char* filename)
{
	char* source;
	int source_len;
	int status_compile;

	source = shader_load(filename);

	if (source == NULL) return -1;

	source_len = strlen(source);
	glShaderSource(id, 1, (const char**)&source, &source_len);

	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &status_compile);
	if (status_compile != GL_TRUE) {
		perror("Error compiling shader!");
		free(source);
		return -1;
	}
	
	shader_program = glCreateProgram();
	glAttachShader(shader_program, id);

	free(source);
	return 0;
}

void shader_init()
{
	int status_link;

	if (shader_program != 0)
	{
		glLinkProgram(shader_program);
		glGetProgramiv(shader_program, GL_LINK_STATUS, &status_link);
		if (status_link != GL_TRUE)
		{
			perror("Error linking shader!");
		} else {
			in_pos_attrib = glGetAttribLocation(shader_program, "in_pos");
			in_color_attrib = glGetAttribLocation(shader_program, "in_color");
		}
	}
}

void shader_remove(void* p)
{
	(void)p;

	glDeleteShader(gl_vertex_shader);
	glDeleteShader(gl_fragment_shader);

	glDeleteProgram(shader_program);
}

