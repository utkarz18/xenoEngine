varying highp vec3 vs_position;
varying highp vec2 vs_tc;

uniform sampler2D texture_2;
uniform int top;

void main()
{
	vec2 tc = vs_tc;
	if (top == 1)
		tc.y = 1.0f - tc.y;
		
	color = texture2D(texture_2, tc);
	if (color.w < 1.0)
		discard;
	//color *= 2.0 / (length(bird - fs_in.position.xy) + 1.5) + 0.5;
	color.w = 1.0;
}