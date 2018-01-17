attribute highp vec4 position;
attribute highp vec2 tc;

uniform highp mat4 pr_matrix;
highp mat4 vw_matrix = mat4(1.0);
highp mat4 ml_matrix = mat4(1.0);

varying highp vec2 vs_tc;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_tc = tc;
}