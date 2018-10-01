#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 Color;
in vec2 LightCenter;
in vec2 FragPos;

void main()
{
	float ambient = 0.1f;
	float spotlight = exp(-7 * sqrt(pow(FragPos.x - LightCenter.x, 2) + pow(FragPos.y - LightCenter.y, 2))) * 10 + 1;
	FragColor = Color * ambient * spotlight;
	FragColor.a = 1;
}