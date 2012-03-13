#version 330

uniform mat4 modelview;
uniform float window_w;
uniform float window_h;
in  vec3 in_Position;
in  vec3 in_Color;
out vec3 ex_Color;

mat4 identity_mat4(void)
{
	return mat4(1.0);
}

// parameters are field of view, aspect ratio, near clip plane, far clip plane
mat4 perspective_standard(const in float fov, const in float aspect, const in float near, const in float far)
{
	return mat4(1.0 / tan(fov), 0.0, 0.0, 0.0,
		0.0, aspect / tan(fov), 0.0, 0.0,
		0.0, 0.0, (far+near)/(far-near), -1.0,
		0.0, 0.0, (-2.0 * (far * near))/(far-near), 0.0);
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
	//mat4 projection = perspective_standard(radians(80.0), 4.0 / 3.0, 0.1, 10000.0);
	mat4 projection = perspective_oblique(-1.0, 1.0, 1.0, -1.0, 0.5, 5.0);
	vec4 pos = (modelview * projection) * vec4(in_Position, 1.0);
	//vec4 pos = modelview * vec4(in_Position, 1.0);
	gl_Position = pos;
	ex_Color = in_Color;
}
