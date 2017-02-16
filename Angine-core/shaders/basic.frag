#version 330 core
in vec2 TexCoords;
out vec4 color;

struct Material 
{
sampler2D texture_diffuse1;
sampler2D texture_ambient1;
sampler2D texture_specular1;
};


uniform Material material;

void main()
{    
    color = texture(material.texture_diffuse1, TexCoords);
}