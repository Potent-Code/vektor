/* GLSL Shaders
 * by Ryan Lucchese
 * January 9 2012 */

#include "glsl_shaders.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void shader_init();
void vertex_shader_init(const char* filename);
void fragment_shader_init(const char* filename);
char* shader_load(const char* filename);
int shader_attach(int id, const char* filename);
void shader_link();
void shaders_resize(int w, int h);
void shader_remove(void* sp);

shader_program shader = NULL;

void shader_init()
{
	if (shader != NULL) return;

	// allocate space for shader_program
	shader = calloc(1, sizeof(*shader));

	// allocate space for vertex shader and fragment shader
	shader->vs = calloc(1, sizeof(*shader->vs));
	shader->fs = calloc(1, sizeof(*shader->fs));

	// bind attributes
	shader->id = glCreateProgram();

	// initialize shaders
	//vertex_shader_init(TRANSFORMS_SHADER);
	vertex_shader_init(VERTEX_SHADER);
	fragment_shader_init(FRAGMENT_SHADER);

	glBindAttribLocation(shader->id, 0, "in_vertex");
	glBindAttribLocation(shader->id, 1, "in_color");

	// link shader
	shader_link();

	// get attribute locations
	shader->vs->in_vertex = glGetAttribLocation(shader->id, "in_vertex");
	shader->vs->in_color = glGetAttribLocation(shader->id, "in_color");

	// get uniform locations
	shader->vs->window_w = glGetUniformLocation(shader->id, "window_w");
	shader->vs->window_h = glGetUniformLocation(shader->id, "window_h");
	shader->vs->view_angle = glGetUniformLocation(shader->id, "view_angle");
	shader->vs->z_near = glGetUniformLocation(shader->id, "z_near");
	shader->vs->z_far = glGetUniformLocation(shader->id, "z_far");

	// camera uniforms
	shader->vs->camera_position = glGetUniformLocation(shader->id, "camera_position");
	shader->vs->camera_pitch = glGetUniformLocation(shader->id, "camera_pitch");
	shader->vs->camera_yaw = glGetUniformLocation(shader->id, "camera_yaw");
}

void vertex_shader_init(const char* filename)
{
	log_add_no_eol("Vertex shader: loading ");
	log_add(filename);
	shader->vs->id = glCreateShader(GL_VERTEX_SHADER);
	shader_attach(shader->vs->id, filename);
}

void fragment_shader_init(const char* filename)
{
	log_add_no_eol("Fragment shader: loading ");
	log_add(filename);
	shader->fs->id = glCreateShader(GL_FRAGMENT_SHADER);
	shader_attach(shader->fs->id, filename);
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
		log_add_no_eol(compile_log);
		free(compile_log);
		if (status_compile != GL_TRUE) return -1;
	}
	
	glAttachShader(shader->id, id);

	free(source);
	return 0;
}

void shader_link()
{
	char* link_log;
	int link_log_len;
	int status_link;

	if (shader->id != 0)
	{
		glLinkProgram(shader->id);
		glGetProgramiv(shader->id, GL_LINK_STATUS, &status_link);
		if (status_link != GL_TRUE)
		{
			log_err("Linking shader failed");
		} else {
			// get link log
			glGetProgramiv(shader->id, GL_INFO_LOG_LENGTH, &link_log_len);
			if (link_log_len > 0)
			{
				link_log = calloc(link_log_len, 1);
				glGetProgramInfoLog(shader->id, link_log_len, NULL, link_log);
				log_add_no_eol(link_log);
				free(link_log);
			}
		}
	}
}

void shaders_resize(int w, int h)
{
	if ((shader != NULL) && (shader->vs != NULL))
	{
		glUniform1f(shader->vs->window_w, (float)w);
		glUniform1f(shader->vs->window_h, (float)h);
	}
}

void shader_remove(void* sp)
{
	(void)sp; // currently we are called from the event loop without an object

	glDeleteShader(shader->vs->id);
	glDeleteShader(shader->fs->id);

	glDeleteProgram(shader->id);
	
	// free shaders
	if(shader->vs != NULL)
	{
		free(shader->vs);
		shader->vs = NULL;
	}
	if (shader->fs != NULL)
	{
		free(shader->fs);
		shader->fs = NULL;
	}
	if (shader != NULL)
	{
		free(shader);
		shader = NULL;
	}
}

