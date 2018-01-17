varying highp vec2 vs_tc;

uniform sampler2D texture_0;

void main()
{
	color = texture2D(texture_0, vs_tc);
}