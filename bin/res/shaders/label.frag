varying highp vec2 vs_tc;
varying highp vec4 vs_color;

uniform sampler2D texture_3;

void main()
{
	gl_FragColor = vs_color * vec4(texture2D(texture_3, vs_tc).b);
	//color = vec4(0.8);
}