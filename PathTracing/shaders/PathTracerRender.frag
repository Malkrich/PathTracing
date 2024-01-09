#version 330 core

uniform sampler2D u_texture;

in vec2 f_texCoord;

out vec4 color;

void main()
{
	vec4 texColor = texture(u_texture, f_texCoord);
	color = texColor;
};