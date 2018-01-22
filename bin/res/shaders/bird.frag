precision highp float;
varying highp vec2 vs_tc;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, vs_tc);
}