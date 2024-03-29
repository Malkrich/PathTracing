#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoord;

out vec2 f_texCoord;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    f_texCoord = a_texCoord;
};