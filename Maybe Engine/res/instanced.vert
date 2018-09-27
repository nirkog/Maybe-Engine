#version 330 core

layout(location = 0) in vec3 v_Pos;
layout(location = 1) in vec3 v_T;//v_MVP0;
//layout(location = 2) in vec4 v_MVP1;
//layout(location = 3) in vec4 v_MVP2;
//layout(location = 4) in vec4 v_MVP3;

out vec4 Color;

void main()
{
	//mat4 mvp = mat4(v_MVP0, v_MVP1, v_MVP2, v_MVP3);
	gl_Position = vec4(v_T * v_Pos, 1.0f);
	Color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}