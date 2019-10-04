#version 330

layout(location = 0) out vec4 OutColor;

in vec4 Color;

void main()
{
	OutColor = Color;
}