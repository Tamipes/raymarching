#version 460 core

layout(location = 0) in vec3 position;
out vec2 uv;

void main()
{
	gl_Position = vec4(position.xyz, 1.0);
	uv = vec2((position.x + 1.0) / 2.0, (position.y + 1.0) / 2.0); //UV ranges from (-1.0; -1.0) to (1.0; 1.0)
}