#version 460 core

layout(location = 0) out vec4 color;

in vec2 UV;

void main()
{
	color = vec4(pow(UV.x, 1.0/2.2), pow(UV.y, 1.0/2.2), 0.0, 1.0);
}