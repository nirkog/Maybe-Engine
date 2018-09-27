#version 330 core

layout(location = 0) in vec3 v_Pos;
layout(location = 1) in vec2 v_TexCoords;

//uniform mat4 u_Model = mat4(1.0f);
//uniform mat4 u_View = mat4(1.0f);
//uniform mat4 u_Proj = mat4(1.0f);

uniform mat4 u_MVP;

out vec2 TexCoords;

void main()
{
	//gl_Position = u_Proj * u_View * u_Model * vec4(v_Pos, 1.0f);
	gl_Position = u_MVP * vec4(v_Pos, 1.0f);
	TexCoords = v_TexCoords;
}