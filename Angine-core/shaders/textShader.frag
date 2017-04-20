#version 330 core 

out vec4 outcolor;

uniform sampler2D texid;
uniform vec3 color;

in VS_OUT
{
 vec2 uv;
} fg_in;


void main()
{
outcolor= vec4( color, texture(texid,fg_in.uv).r);
}