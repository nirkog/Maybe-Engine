#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float v_Tid;
layout(location = 3) in vec3 v_Color;

uniform mat4 u_View;// = mat4(1);
uniform mat4 u_Proj;// = mat4(1);

out vec4 Color;
out vec2 FragPos;
out vec2 uvCoords;
flat out int tid;

void main()
{
	gl_Position = u_Proj * u_View * vec4(position, 1);
	Color = vec4(v_Color.xyz, 1);
	FragPos = vec2(gl_Position.xy);
	uvCoords = uv;
	tid = int(v_Tid * 32);
}