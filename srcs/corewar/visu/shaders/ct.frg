#version 410 core

out vec4	fragColor;
in vec4	vtxColor;

uniform mainBlock
{
	mat4 projView;
	vec2 res;
	float ratio;
	float time;
	float intro;
	float bass;
	float speed;
}u;

void	main()
{
	fragColor = vtxColor;
}
