#version 120

varying vec2 vertex_tcoords;
varying vec3 vertex_color;

uniform sampler2D texture_sampler;

void main(void)
{
	vec4 texture_color = texture2D(texture_sampler, vertex_tcoords);
	gl_FragColor = texture_color * vec4(vertex_color,1.0);
}
