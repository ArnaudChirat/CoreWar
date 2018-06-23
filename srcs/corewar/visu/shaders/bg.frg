#version 410 core

out vec4	fragColor;
//layout(origin_upper_left) in vec4 gl_FragCoord;

uniform mainBlock
{
	mat4 projView;
	vec2 res;
	float ratio;
	float time;
	float intro;
}m;

uniform	raymarchBlock
{
	vec3	eye;
}r;

const int	max_it = 30;
const float	max_fit = 30.;
const float max_dst = 500.;

vec2	frag_to_ndc()
{
	return (vec2(((gl_FragCoord.x / 2560.) * 2. - 1.) * m.ratio,
					(gl_FragCoord.y / 1440.) * 2. - 1.));
}
float	sphere(vec3 ray, float d)
{
		return (length(ray) - d);
}

float	cube(vec3 ray, float d)
{
		vec3 q = abs(ray) - d;
			return min(max(q.z, max(q.x,q.y)), 0.0) + length(max(q, 0.0));
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
		return (length(vec2(ray.x + 2. * cos(ray.z * 0.3 * (cos(m.time * 0.0001) + 1.)), ray.y + 2. * sin(ray.z * 0.3 * (sin(m.time * 0.0003) + 1.)))) - d);
}

float	cylinderfk2(vec3 ray, float d)
{
		return (length(vec2(ray.x + 2. * cos(ray.x * 0.3 * (cos(m.time * 0.0001) + 1.)), ray.y + 2. * sin(ray.y * 0.3 * (sin(m.time * 0.0003) + 1.)))) - d);
}

float	plane(float ray, float d)
{
		return (ray - d);
}

vec3		twist(vec3 ray)
{
		float c = cos(20.0 * ray.y);
			float s = sin(20.0 * ray.z);
				mat2 mt = mat2(c, -s * cos(m.time), s, c * sin(m.time));
					return (vec3(vec2(mt * ray.xz), ray.y));
}

vec3		repeat3(vec3 ray, float rem)
{
		return (mod(ray, rem) - 0.5 * rem);
}

vec2		repeat2(vec2 ray, float rem)
{
		return (mod(ray, rem) - 0.5 * rem);
}

float		repeat1(float ray, float rem)
{
		return (mod(ray, rem) - 0.5 * rem);
}

vec3		fk(vec3 ray, float f)
{
		return(vec3(ray.x + cos(ray.z * 0.1 * cos(m.time * 0.0001)) * f, ray.y + cos(ray.z * 0.1 * sin(m.time * 0.0001)) * f, ray.z));
}

vec3		bfk(vec3 ray, float f)
{
		return(vec3(ray.x + cos(ray.z * 0.1 * cos(m.time * 0.0002)) * f, ray.y + cos(ray.z * 0.1 * sin(m.time * 0.0002)) * f, ray.z));
}

vec3		sfk(vec3 ray, float f)
{
		return(vec3(ray.y + cos(ray.z * 0.1 * sin(m.time * 0.0001)) * f, ray.x + cos(ray.z * 0.1 * cos(m.time * 0.0001)) * f, ray.z));
}

vec3		msfk(vec3 ray, float f)
{
		return(vec3(-ray.x + cos(ray.z * 0.1 * sin(m.time * 0.0001)) * f, -ray.y + cos(ray.z * 0.1 * cos(m.time * 0.0001)) * f, ray.z));
}

vec3		roty(vec3 ray, float ct, float st)
{
		return vec3(ray.x * ct + ray.z * st, ray.y, ray.z * ct + ray.x * -st);
}

vec3		rotx(vec3 ray, float ct, float st)
{
		return vec3(ray.x, ray.y * ct + ray.z * st, ray.z * ct + ray.y * -st);
}

vec3		rotz(vec3 ray, float ct, float st)
{
		return vec3(ray.x * ct + ray.y * st, ray.y * ct + ray.x * -st, ray.z);
}

vec2	map(vec3 eye, vec3 rd)
{
	int	i = 0;
	vec3 ray = eye;
	float dst;
	vec3 follow;
	vec3 ct = vec3(cos(m.time * 0.3), cos(m.time * 0.3 + 0.78),
							cos(m.time * 0.3 + 3.76));
	vec3 st = vec3(sin(m.time * 0.3), sin(m.time * 0.3 + 0.78),
							sin(m.time * 0.3 + 3.76));

	while (i < max_it)
	{
		follow = vec3(ray.x - eye.x - 11., ray.yz - eye.yz);
		dst = 
			max(-cube(roty(rotx(rotz(vec3(ray.xy, repeat1(ray.z, 50))
						, ct.x, st.x), ct.y, st.y), ct.z, st.z), 40.),
			-cube(rotz(rotx(rotx(vec3(ray.xy, repeat1(ray.z, 75))
						, ct.x, st.x), ct.y, st.y), ct.z, st.z), 40.));
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

	vec3 tar = vec3(0., 0.0, m.time * 60.);
	vec3 eye = vec3(r.eye.xy, r.eye.z + m.time * 60.);
	vec3 up = vec3(0., 1.0, 0.0);

	//PS3 CONTROLS
	//eye = s_eye; tar = s_tar; up = s_up;

	vec3 z_vec = normalize(tar - eye);
	vec3 x_vec = normalize(cross(z_vec, up));
	vec3 y_vec = normalize(cross(x_vec, z_vec));

	vec3 rd = normalize(x_vec * uv.x + y_vec * uv.y + z_vec * 2.);
	
	vec2 ret = map(eye, rd);
	fragColor = vec4(
					1. - ret.x * 1.6 / (ret.y + 0.8) + 0.01 * cos(m.time),
					1. - ret.x * 1.6 / (ret.y + 0.8) + 0.01 * cos(m.time + 2.),
					1. - ret.x * 1.6 / (ret.y + 0.8) + 0.01 * cos(m.time + 4.),
					1.0);
	fragColor.xyz = pow(fragColor.xyz, vec3(10.5 + cos(m.time * 2.) * 0.2
													- m.intro * 1.));
}
