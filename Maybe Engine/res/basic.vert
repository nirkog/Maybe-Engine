#version 330 core

layout(location = 0) in vec2 v_Pos;

void main()
{
	gl_Position = vec4(v_Pos, 0.0f, 1.0f);
}