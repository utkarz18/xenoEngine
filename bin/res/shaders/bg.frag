precision highp float;
varying highp vec3 vs_position;
varying highp vec2 vs_tc;

uniform sampler2D tex;

void main()
{
	vec4 color = texture2D(tex, vs_tc);
	color *= 2.0 / (length(vs_position.xy) + 2.5) + 0.5;
	gl_FragColor = color;
}