#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 v_Color;

uniform mat4 u_View = mat4(1);
uniform mat4 u_Proj = mat4(1);

out vec4 Color;

void main()
{
	gl_Position = u_Proj * u_View * position;
	Color = vec4(v_Color, 1.0f);
}