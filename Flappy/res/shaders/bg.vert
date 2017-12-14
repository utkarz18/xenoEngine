#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);

out DATA
{
	vec2 uv;
	vec3 position;
	float tid;
	vec4 color;
}vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
	vs_out.position = vec3(vw_matrix * position);
}