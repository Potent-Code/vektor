#version 330

in  vec3 vertex_color; // from vertex shader
out vec4 frag_color;

void main(void)
{
       frag_color = vec4(vertex_color, 1.0);
}
