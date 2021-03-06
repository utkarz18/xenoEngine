precision highp float;

varying highp vec3 vs_position;
varying highp vec2 vs_tc;

uniform sampler2D tex;
uniform int top;

void main()
{
	vec2 tc = vs_tc;
	if (top == 1)
		tc.y = 1.0 - tc.y;
		
	vec4 color = texture2D(tex, tc);
	if (color.w < 1.0)
		discard;
	color *= 2.0 / (length(vs_position.xy) + 1.5) + 0.5;
	color.w = 1.0;
	gl_FragColor = color;
}