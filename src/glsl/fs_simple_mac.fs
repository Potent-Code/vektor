#version 120

varying vec4 vertex_color; // from vertex shader
varying vec2 vertex_tcoords;

uniform sampler2D texture_sampler;

void main(void)
{
	vec4 texture_color;
	texture_color = texture2D(texture_sampler, vertex_tcoords);
	gl_FragColor = texture_color * vertex_color;
}
