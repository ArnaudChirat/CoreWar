#version 410 core

out vec4	fragColor;
//layout(origin_upper_left) in vec4 gl_FragCoord;

in vec3		ct;
in vec3		st;

uniform mainBlock
{
	mat4 projView;
	vec2 res;
	float ratio;
	float time;
	float intro;
	float bass;
	float speed;
}m;

uniform	raymarchBlock
{
	vec3	eye;
}r;

const int	max_it = 40;
const float	max_fit = 40.;
const float max_dst = 2000.;

vec2	frag_to_ndc()
{
	return (vec2(((gl_FragCoord.x / 2560.) * 2. - 1.) * m.ratio,
					(gl_FragCoord.y / 1440.) * 2. - 1.));
}

float	sphere(vec3 ray, float d)
{
	return (length(ray) - d);
}

float	spherefk(vec3 ray, float d)
{
	return (length(vec3(ray.x + cos(ray.z) * cos(m.time), ray.y + cos(ray.z) * sin(m.time), ray.z)) - d);
}

float	cylinder(vec3 ray, float d)
{
	return (length(ray.xy) - d);
}

float	cylinderfk(vec3 ray, float d)
{
	return (length(vec2(ray.x + 2. * cos(ray.z * 0.3 * (cos(m.time * 0.0003) + 1.)), ray.y + 2. * sin(ray.z * 0.3 * (sin(m.time * 0.0003) + 1.)))) - d);
}
float	plane(float ray, float d)
{
	return (ray - d);
}

vec3		twist(vec3 ray)
{
	float c = cos(4.0 * ray.y);
	float s = sin(4.0 * ray.x);
	mat2 mt = mat2(c, -s * cos(m.time), s, c * sin(m.time));
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
	vec3 tar = vec3(3.5 * cos(m.time * 0.1), 0.0, 3.5 * sin(m.time * 0.1));
	vec3 up = vec3(0.0, 1.0, 0.0);
	*/

	//Going forward rotating
	/*
	vec3 eye = vec3(0.0, 0.0, -m.time * 0.5 + 1.0);
	vec3 tar = vec3(0.0, 0.0, -m.time * 0.5);
	vec3 up = vec3(1.0 * sin(m.time * 0.4), 1.0 * cos(m.time * 0.4), 0.0);
	*/

	vec3 eye = vec3(r.eye.z + m.time * 15., r.eye.y, -r.eye.x);
	vec3 tar = vec3(m.time * 15. + 1.0, 0.0, 0.0);
	vec3 up = vec3(0.0, 1.0, 0.0);

	vec3 z_vec = normalize(tar - eye);
	vec3 x_vec = normalize(cross(z_vec, up));
	vec3 y_vec = normalize(cross(x_vec, z_vec));

	vec3 rd = normalize(x_vec * uv.x + y_vec * uv.y + z_vec * 1.0);
	
	vec2 ret = map(eye, rd);
	fragColor = vec4(ret.x / ret.y, ret.x / ret.y, max(ret.x / ret.y, ret.y * 0.2), 1.);
	fragColor.xyz = pow(fragColor.xyz, vec3(0.5));
}
/*
	vec3 tar = vec3(0., 0.0, m.time * 60.);
	vec3 eye = vec3(r.eye.xy, r.eye.z + m.time * 60.);
	vec3 up = vec3(0., 1.0, 0.0);
	*/
