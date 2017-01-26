#version 330 core 

layout(location=0) in vec3 pos ;
layout(location = 1 ) in vec3  in_color ;
layout(location =1 ) in vec2 in_texCoord;

out vec3  out_color ;
out vec2 texCoord;
void main ()
{

gl_Position= vec4(pos.x , pos.y, pos.z , 1.0);

out_color =in_color ;
texCoord = in_texCoord;
}