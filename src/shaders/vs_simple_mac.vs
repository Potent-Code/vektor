#version 120

// Vekter vertex shader
// by Ryan Lucchese
// March 15 2012

// view port uniforms
uniform float window_w; // window width
uniform float window_h; // window height
uniform float view_angle; // field of view in degrees
uniform float z_near; // near clip plane
uniform float z_far; // far clip plane

// transformation uniforms
uniform int projection_type;
uniform vec3 camera_position; // position vector of camera
uniform float camera_pitch; // mouse angles
uniform float camera_yaw;

// inputs and outputs
attribute vec3 in_vertex;
attribute vec3 in_color;
attribute vec2 in_tcoords;
varying vec3 vertex_color;
varying vec2 vertex_tcoords;

// a set of transformations for constructing a view
// by Ryan Lucchese
// March 15 2012

// parameters are field of view, aspect ratio, near clip plane, far clip plane
mat4 transform_perspective_standard(const in float fov, const in float aspect, const in float n, const in float f)
{
	return mat4(	1.0/tan(fov),	0.0,		0.0,		0.0,
			0.0,	aspect/tan(fov), 	0.0,		0.0,
			0.0,		0.0, 		(f+n)/(n-f),	-1.0,
			0.0,		0.0, 	(-2.0*(f*n))/(f-n),	 0.0);
}
			
// parameters are left, right, bottom, top, (screen coordinates) near, far (clip planes)
mat4 transform_perspective_oblique(const in float l, const in float r, const in float b, const in float t, const in float n, const in float f)
{
	return mat4(	(2.0*n)/(r-l),	0.0,		0.0,			0.0,
			0.0,		(2.0*n)/(t-b),	0.0,			0.0,
			(r+l)/(r-l),	(t+b)/(t-b),	-((f+n)/(f-n)),		-1.0,
			0.0,		0.0,		-((2.0*(f*n))/(f-n)),	0.0);
}

// parameters are left, right, bottom, top, (screen coordinates) near, far (clip planes)
mat4 transform_orthographic(const in float l, const in float r, const in float b, const in float t, const in float n, const in float f)
{
	return mat4(	(2.0/(r-l)),	0.0,		0.0,		0.0,
			0.0,		(2.0/(t-b)),	0.0,		0.0,
			0.0,		0.0,		-(2.0/(f-n)),	0.0,
			-((r+l)/(r-l)),	-((t+b)/(t-b)),	-((f+n)/(f-n)),	1.0);
}

// 3D Euclidean group transformations E(3)
mat4 transform_rotate_x(const in float angle)
{
	mat4 rx = mat4(1.0);
	rx[1][1] = cos(angle);
	rx[2][1] = sin(angle);
	rx[1][2] = -sin(angle);
	rx[2][2] = cos(angle);
	return rx;
}

mat4 transform_rotate_y(const in float angle)
{
	mat4 ry = mat4(1.0);
	ry[0][0] = cos(angle);
	ry[2][0] = -sin(angle);
	ry[0][2] = sin(angle);
	ry[2][2] = cos(angle);
	return ry;
}

mat4 transform_rotate_z(const in float angle)
{
	mat4 rz = mat4(1.0);
	rz[0][0] = cos(angle);
	rz[1][0] = sin(angle);
	rz[0][1] = -sin(angle);
	rz[1][1] = cos(angle);
	return rz;
}

mat4 transform_translate(const in vec3 loc)
{
	return mat4(	1.0,	0.0,	0.0,	0.0,
			0.0,	1.0,	0.0,	0.0,
			0.0,	0.0,	1.0,	0.0,
			loc.x,	loc.y,	loc.z,	1.0);
}

void main(void)
{
	// calculate modelview transformation
	mat4 modelview = (transform_rotate_x(camera_pitch) * transform_rotate_y(camera_yaw)) * transform_translate(camera_position);

	// calculate projection transformation
	mat4 projection = mat4(1.0);
	switch (projection_type)
	{
		case 1: // standard perspective transformation
			projection = transform_perspective_standard(radians(view_angle), (window_w / window_h), z_near, z_far);
			break;
		case 2: // oblique perspective transformation
			projection = transform_perspective_oblique(0.0, window_w, 0.0, window_h, z_near, z_far);
			break;
		case 3: // orthographic projection
			projection = transform_orthographic(-window_w/2.0, window_w/2.0, -window_h/2.0, window_h/2.0, -1.0, 1.0);
			modelview = mat4(1.0);
			break;
		default: // no projection
			break;
	}

	// output of vertex shader
	gl_Position = projection * (modelview * vec4(in_vertex, 1.0));
	vertex_color = in_color;
	vertex_tcoords = in_tcoords;
}

