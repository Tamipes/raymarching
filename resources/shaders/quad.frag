#version 460 core

#define PI 3.1415923

layout(location = 0) out vec4 color;
in vec2 uv;

// camera (y - vertical component; x,z - horizontal components)
vec3 uCamPos = vec3(1.0, 0.0, 0.0);
vec3 uLookAt = vec3(0.0, 0.0, 0.0);
float uFOV = PI * 0.333;
vec3 up = vec3(0.0, 1.0, 0.0);
float focal_length = 3.0;

float aspect_ratio = 16.0 / 9.0;

// marching
int max_iter = 3200;
float min_dist = .001;
float max_dist = 1000.;

// debug sphere
float radius = 0.25;
vec3 sphere_pos = vec3(0.0, 0.0, 0.0);

// sun
vec3 sun_dir = normalize(vec3(1.0, 1.0, 1.0));


// utils
float clamp(float a)
{
    return min(max(a, 0.0), 1.0);
}

float map(float a, float iMin, float iMax, float oMin, float oMax)
{
    return oMin + (a - iMin) / (iMax - iMin) * (oMax - oMin);
}

// SDFs
float SDF_sphere(vec3 ray_pos, vec3 sphere_pos, float r)
{
	return length(sphere_pos - ray_pos) - r;
}


// main rendering function
void main(void)
{
	vec3 look_dir = normalize(uLookAt - uCamPos);
	vec3 half_horizontal = normalize(cross(up, look_dir)) * tan(uFOV * 0.5) * focal_length;
	vec3 half_vertical = normalize(cross(look_dir, half_horizontal)) * tan(uFOV * 0.5) * focal_length / aspect_ratio;

	vec2 centeredUV = uv - vec2(0.5);
	vec3 canvas_pos = look_dir * focal_length + 2.0 * (centeredUV.x * half_horizontal + centeredUV.y * half_vertical);
	vec3 ray_dir = normalize(canvas_pos);

	vec3 ray_pos = uCamPos;
	float ray_dist = 0.0;
	for (int i = 0; i < max_iter && ray_dist <= max_dist; i++)
	{
		float dist = max_dist + 1.0;
		dist = min(dist, SDF_sphere(ray_pos, sphere_pos, radius));

		if (dist < min_dist)
		{
			vec3 normal = normalize(ray_pos - sphere_pos);			
			color = vec4(vec3(0.0, 1.0, .5) * (dot(normal, sun_dir) + 1.0) * 0.5, 1.0);
			return;
		}

		ray_pos += ray_dir * dist;
		ray_dist += dist;
	}

	color = vec4(vec3(0.0), 1.0);
}