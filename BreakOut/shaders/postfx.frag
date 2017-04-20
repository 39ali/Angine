#version 330 core 

out vec4 color ;

in vec2 out_texCoords;

uniform sampler2D  textureId;

 

void main()
{
    color = vec4(1,1,1,1);//texture(textureId,out_texCoords);
}  