attribute highp vec4 position;
attribute highp vec2 tc;

uniform highp mat4 pr_matrix;
uniform highp mat4 vw_matrix;

varying highp vec2 vs_tc;
varying highp vec3 vs_position;

void main()
{
	gl_Position = pr_matrix * vw_matrix * position;
	vs_tc = tc;
	vs_position = vec3(vw_matrix * position);
}