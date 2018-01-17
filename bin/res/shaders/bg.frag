varying highp vec4 vs_position;
varying highp vec2 vs_tc;

uniform highp sampler2D texture_1;

void main()
{
	color = texture2D(texture_1, vs_tc);
	//color *= 2.0 / (length(bird - fs_in.position.xy) + 2.5) + 0.5;
}