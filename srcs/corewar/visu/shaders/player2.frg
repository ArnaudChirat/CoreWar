#version 410 core

out vec4	fragColor;

uniform mainBlock
{
	mat4 projView;
	vec2 res;
	float ratio;
	float time;
	float intro;
	float bass;
}u;

uniform	raymarchBlock
{
	vec3	eye;
}r;

const int	max_it = 80;
const float	max_fit = 80.;
const float max_dst = 150.;

vec2	frag_to_ndc()
{
	return (vec2(((gl_FragCoord.x / u.res.x) * 2. - 1.) * u.ratio,
					(gl_FragCoord.y / u.res.y) * 2. - 1.));
}
float	sphere(vec3 ray, float d)
{
	return (length(ray) - d);
}

float	spherefk(vec3 ray, float d)
{
	return (length(vec3(ray.x + cos(ray.z) * cos(u.time), ray.y + cos(ray.z) * sin(u.time), ray.z)) - d);
}

float	cylinder(vec3 ray, float d)
{
	return (length(ray.xy) - d);
}

float	cylinderfk(vec3 ray, float d)
{
	return (length(vec2(ray.x + 2. * cos(ray.z * 0.3 * (cos(u.time * 0.0003) + 1.)), ray.y + 2. * sin(ray.z * 0.3 * (sin(u.time * 0.0003) + 1.)))) - d);
}
float	plane(float ray, float d)
{
	return (ray - d);
}

vec3		twist(vec3 ray)
{
	float c = cos(4.0 * ray.y);
	float s = sin(4.0 * ray.x);
	mat2 mt = mat2(c, -s * cos(u.time), s, c * sin(u.time));
	return (vec3(vec2(mt * ray.xy), ray.z));
}

vec3		repeat3(vec3 ray, float rem)
{
	return (mod(ray, rem) - 0.5 * rem);
}

vec2		repeat2(vec2 ray, float rem)
{
	return (mod(ray, rem) - 0.5 * rem);
}

vec2	map(vec3 eye, vec3 rd)
{
	int	i = 0;
	vec3 ray = eye;
	float dst;

	while (i < max_it)
	{
		dst = max(-cylinderfk(ray.yzx, 6.), sphere(repeat3(ray, 5.9), 3.75));
		if (dst < 0.01 || length(ray - eye) > max_dst)
			break;
		ray = ray + dst * rd;
		i++;
	}
	return (vec2(length(ray - eye) / max_dst, i / max_fit));
}

void	main()
{
	vec2 uv = frag_to_ndc();

	//Looking around
	/*
	vec3 eye = vec3(0.0, 0.0, 0.0);
	vec3 tar = vec3(3.5 * cos(u.time * 0.1), 0.0, 3.5 * sin(u.time * 0.1));
	vec3 up = vec3(0.0, 1.0, 0.0);
	*/

	//Going forward rotating
	/*
	vec3 eye = vec3(0.0, 0.0, -u.time * 0.5 + 1.0);
	vec3 tar = vec3(0.0, 0.0, -u.time * 0.5);
	vec3 up = vec3(1.0 * sin(u.time * 0.4), 1.0 * cos(u.time * 0.4), 0.0);
	*/

	vec3 eye = vec3(r.eye.z + u.time * 15., r.eye.y, -r.eye.x);
	vec3 tar = vec3(u.time * 15. + 1.0, 0.0, 0.0);
	vec3 up = vec3(0.0, 1.0, 0.0);

	vec3 z_vec = normalize(tar - eye);
	vec3 x_vec = normalize(cross(z_vec, up));
	vec3 y_vec = normalize(cross(x_vec, z_vec));

	vec3 rd = normalize(x_vec * uv.x + y_vec * uv.y + z_vec * 1.0);
	
	vec2 ret = map(eye, rd);
	fragColor = vec4(ret.x, ret.x * ret.y * 3., ret.y, 1.);
}
