#version 330

in vec3 vertex_color; // from vertex shader
in vec2 vertex_tcoords;
out vec4 frag_color;

uniform sampler2D texture_sampler;

void main(void)
{
	vec4 texture_color;
	if (vertex_tcoords != vec2(0.0, 0.0))
	{
		texture_color = texture2D(texture_sampler, vertex_tcoords);
		frag_color = texture_color * vec4(vertex_color, 1.0);
	} else {
		frag_color = vec4(vertex_color, 1.0);
	}
}
