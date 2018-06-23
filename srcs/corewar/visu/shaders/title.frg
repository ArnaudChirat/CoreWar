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
}u;

const int	max_it = 40;
const float	max_fit = 40.;
const float max_dst = 10.;

vec2	frag_to_ndc()
{
	return (vec2(((gl_FragCoord.x / u.res.x) * 2. - 1.) * u.ratio,
					(gl_FragCoord.y / u.res.y) * 2. - 1.));
}
float	sphere(vec3 ray, float d)
{
	vec3 q = fract(ray * 0.4) * 2. - 1.;
	return (length(q) - d);
}

float	cylinder(vec2 ray, float d, float rem)
{
	vec2 q = fract(ray * rem) * (rem * 8.) - (rem * 4.);
	return (length(q) - d);
}

vec2	map(vec3 eye, vec3 rd)
{
	int	i = 0;
	vec3 ray = eye;
	float dst;

	while (i < max_it)
	{
		dst = max(-cylinder(ray.xx, 2., 0.5), cylinder(ray.yy, 2., 0.5));
		if (dst < 0.01 || length(ray - eye) > max_dst)
			break;
		ray = ray + dst * rd;
		i++;
	}
	return (vec2(length(ray - eye) / max_dst, float(i * cos(u.time)) / max_fit));
}

void	main()
{
	vec2 uv = frag_to_ndc();

	//Looking around
	vec3 eye = vec3(0.0, 0.0, 0.0);
	vec3 tar = vec3(3.5 * cos(u.time * 1.1), 0.0, 3.5 * sin(u.time * 1.1));
	vec3 up = vec3(0.0, 1.0, 0.0);

	/*
	//Going forward rotating
	vec3 eye = vec3( 1.0, 0.0, 0.0);
	vec3 tar = vec3(0.0, 0.0, 0.0);
	vec3 up = vec3(1.0 * sin(u.time), 1.0 * cos(u.time), 0.0);
	*/

	/*
	vec3 eye = vec3(1.0, u.time, 1.0);
	vec3 tar = vec3(1. + cos(u.time * 0.4), u.time, 1. + sin(u.time * 0.4));
	vec3 up = vec3(0.0, 1.0, 0.0);
	*/

	vec3 z_vec = normalize(tar - eye);
	vec3 x_vec = normalize(cross(z_vec, up));
	vec3 y_vec = normalize(cross(x_vec, z_vec));

	vec3 rd = normalize(x_vec * uv.x + y_vec * uv.y + z_vec * 1.0);
	
	vec2 ret = map(eye, rd);
	fragColor = vec4(ret.x,
					1.0 * (ret.x - ret.y) * cos(u.time),
					mix(max(1. - abs(uv.x), 1. - abs(uv.y)), ret.x, 0.1),
					1.0);
}
