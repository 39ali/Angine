#version 330 core 

out vec4 color ; 

uniform sampler2D texid;

in vec2 out_texcoords;

void main ()
{

color = texture(texid,out_texcoords);
};