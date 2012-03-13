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
void shaders_resize(int w, int h);
void shader_remove(void* p);

int gl_vertex_shader = 0;
int gl_fragment_shader = 0;
int shader_program = 0;

int in_pos_attrib = 0;
int in_color_attrib = 0;
int mvp_loc = 0;
int ww_loc = 0;
int wh_loc = 0;

void vertex_shader_install(const char* filename)
{
	log_add_no_eol("Vertex shader: loading ");
	log_add(filename);
	gl_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	shader_attach(gl_vertex_shader, filename);
}

void fragment_shader_install(const char* filename)
{
	log_add_no_eol("Fragment shader: loading ");
	log_add(filename);
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
		log_err_sys("Could not open shader file");
		return NULL;
	}

	stat(filename, &filestat);
	source_len = filestat.st_size;

	if((source = calloc(source_len, 1)) == NULL)
	{
		log_err("calloc failed");
		return NULL;
	}

	bytes_read = fread(source, 1, source_len, fd);
	if (bytes_read != source_len)
	{
		log_err("There was a problem reading the file");
		free(source);
		return NULL;
	}

	fclose(fd);

	return source;
}

int shader_attach(int id, const char* filename)
{
	char* source = NULL;
	char* compile_log = NULL;
	int source_len = 0;
	int compile_log_len = 0;
	int status_compile;

	source = shader_load(filename);

	if (source == NULL) return -1;

	source_len = strlen(source);
	glShaderSource(id, 1, (const char**)&source, &source_len);

	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &status_compile);
	if (status_compile != GL_TRUE) {
		log_err("Compiling shader failed");
		free(source);
		source = NULL;
	}

	// get compile log
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &compile_log_len);
	if (compile_log_len > 0)
	{
		compile_log = calloc(compile_log_len, 1);
		glGetShaderInfoLog(id, compile_log_len, NULL, compile_log);
		log_add(compile_log);
		free(compile_log);
		if (status_compile != GL_TRUE) return -1;
	}
	
	if (shader_program == 0)
	{
		shader_program = glCreateProgram();
		glBindAttribLocation(shader_program, 0, "in_Position");
		glBindAttribLocation(shader_program, 1, "in_Color");
	}
	glAttachShader(shader_program, id);

	free(source);
	return 0;
}

void shader_init()
{
	char* link_log;
	int link_log_len;
	int status_link;

	if (shader_program != 0)
	{
		glLinkProgram(shader_program);
		glGetProgramiv(shader_program, GL_LINK_STATUS, &status_link);
		if (status_link != GL_TRUE)
		{
			log_err("Linking shader failed");
		} else {
			in_pos_attrib = glGetAttribLocation(shader_program, "in_Position");
			in_color_attrib = glGetAttribLocation(shader_program, "in_Color");
			mvp_loc = glGetUniformLocation(shader_program, "modelview");
			ww_loc = glGetUniformLocation(shader_program, "window_w");
			wh_loc = glGetUniformLocation(shader_program, "window_h");

			// get link log
			glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &link_log_len);
			if (link_log_len > 0)
			{
				link_log = calloc(link_log_len, 1);
				glGetProgramInfoLog(shader_program, link_log_len, NULL, link_log);
				log_add(link_log);
				free(link_log);
			}
		}
	}
}

void shaders_resize(int w, int h)
{
	glUniform1f(ww_loc, (float)w);
	glUniform1f(wh_loc, (float)h);
}

void shader_remove(void* p)
{
	(void)p;

	glDeleteShader(gl_vertex_shader);
	glDeleteShader(gl_fragment_shader);

	glDeleteProgram(shader_program);
}

