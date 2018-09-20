#version 330 core

layout(location = 0) in vec3 v_Pos;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_View = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(v_Pos, 1.0f);
}