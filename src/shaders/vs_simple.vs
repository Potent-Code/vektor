#version 330

// view port uniforms
uniform mat4 modelview; // transformation matrix
uniform float window_w; // window width
uniform float window_h; // window height
uniform float view_angle; // field of view in degrees
uniform float z_near; // near clip plane
uniform float z_far; // far clip plane

in  vec3 in_vertex;
in  vec3 in_color;
out vec3 vertex_color;

// parameters are field of view, aspect ratio, near clip plane, far clip plane
mat4 perspective_standard(const in float fov, const in float aspect, const in float n, const in float f)
{
	return mat4(	1.0/tan(fov),	0.0,		0.0,		0.0,
			0.0,	aspect/tan(fov), 	0.0,		0.0,
			0.0,		0.0, 		(f+n)/(n-f),	-1.0,
			0.0,		0.0, 	(-2.0*(f*n))/(f-n),	 0.0);
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
	//mat4 projection = perspective_standard(radians(45.0), 4.0 / 3.0, 0.5, 500.0);
	gl_Position = projection * (modelview * vec4(in_vertex, 1.0));
	vertex_color = in_color;
}
