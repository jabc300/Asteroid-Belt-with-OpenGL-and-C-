#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

in VS_OUT
{
    vec2 texCoords;
} fs_in;

void main()
{
    FragColor = texture(texture_diffuse1, fs_in.texCoords);
}
