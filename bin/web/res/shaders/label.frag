#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D tex;

in DATA
{
	vec2 tc;
	vec4 color;
}fs_in;

void main()
{
	color = fs_in.color * vec4(texture(tex, fs_in.tc).b);
	//color = vec4(0.8);
}