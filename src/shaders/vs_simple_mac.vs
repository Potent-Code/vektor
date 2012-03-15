#version 120

// uniforms
uniform mat4 modelview;
uniform float window_w;
uniform float window_h;
uniform float view_angle;
uniform float z_near;
uniform float z_far;

// attributes
attribute  vec3 in_vertex;
attribute  vec3 in_color;

// outputs
varying vec3 vertex_color;

// parameters are field of view, aspect ratio, near clip plane, far clip plane
mat4 perspective_standard(const in float fov, const in float aspect, const in float n, const in float f)
{
        return mat4(    1.0/tan(fov),   0.0,            0.0,            0.0,
                        0.0,    aspect/tan(fov),        0.0,            0.0,
                        0.0,            0.0,            (f+n)/(n-f),    -1.0,
                        0.0,            0.0,    (-2.0*(f*n))/(f-n),      0.0);
}

// parameters are left, right, top, bottom, (screen coordinates) near, far (clip planes)
mat4 perspective_oblique(const in float l, const in float r, const in float t, const in float b, const in float n, const in float f)
{
	return mat4(	(2*n)/(r-l),	0,		0,		0,
			0,		(2*n)/(t-b),	0,		0,
			(r+l)/(r-l),	(t+b)/(t-b),	-((f+n)/(f-n)),	-1,
			0,		0,		-((2*(f*n))/(f-n)), 0);
}

void main(void)
{
	mat4 projection = perspective_standard(radians(view_angle), (window_w / window_h), z_near, z_far);
	gl_Position = projection * (modelview * vec4(in_vertex, 1.0));
	vertex_color = in_color;
}
