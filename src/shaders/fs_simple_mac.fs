#version 120

//precision highp float; // needed only for version 1.30

varying  vec3 ex_Color;
varying vec4 out_Color;

void main(void)
{
       out_Color = vec4(ex_Color,1.0);
}
