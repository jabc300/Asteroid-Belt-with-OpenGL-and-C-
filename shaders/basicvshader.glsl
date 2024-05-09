#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aOffset;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    vec3 pos = aPos * (gl_InstanceID/100.0);
    gl_Position = projection * view * model * vec4(pos + aOffset, 1.0);
}