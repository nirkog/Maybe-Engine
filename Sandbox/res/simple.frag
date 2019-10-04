#version 330

layout(location = 0) out vec4 o_Color;

in vec3 Color;

void main()
{
	o_Color = vec4(Color, 1);
	//o_Color = vec4(TexCoord, 0, 1) * u_Color;
	//o_Color = texture(u_Texture, TexCoord);
}