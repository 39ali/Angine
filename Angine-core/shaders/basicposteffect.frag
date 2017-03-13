#version 330 core 

out vec4 color ;

in vec2 out_texCoords;

uniform sampler2D  textureId;

 

void main()
{
    color = texture(textureId,out_texCoords);
}  