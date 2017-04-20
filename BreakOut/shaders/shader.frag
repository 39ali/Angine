#version 330 core 

out vec4 color;

in vec2 out_uv;
uniform sampler2D img;
uniform vec3 objcolor;

void main ()
{
color =vec4(objcolor,1.0f)* texture(img,out_uv);
}