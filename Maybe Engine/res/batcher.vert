#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_Color;

uniform mat4 u_View;// = mat4(1);
uniform mat4 u_Proj;// = mat4(1);

uniform vec2 u_LightCenter = vec2(0, 0);

out vec4 Color;
out vec2 LightCenter;
out vec2 FragPos;

void main()
{
	gl_Position = u_Proj * u_View * vec4(position, 1);
	Color = v_Color;
	LightCenter = u_LightCenter;
	FragPos = vec2(gl_Position.xy);
}