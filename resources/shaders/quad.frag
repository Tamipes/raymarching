#version 460 core

layout(location = 0) out vec4 color;

in vec2 UV;

void main()
{
	color = vec4(UV.xy, 1.0, 1.0);
}