#version 330

layout(location = 0) in vec2 v_Pos;
layout(location = 1) in vec2 v_TexCoord;
layout(location = 2) in vec3 v_Color;

out vec3 Color;

void main()
{
	gl_Position = vec4(v_Pos, 0, 1);

	Color = v_Color;
}