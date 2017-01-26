#version 330 core 

layout(location = 0)out vec4 color;
layout ( location = 1) in  vec2 texCoord;
in  vec3 out_color;


uniform sampler2D tex ;

void main ()
{
	

color =  texture(tex ,texCoord) ;//  vec4(1.0f, 0.5f, 0.2f, 1.0f);

}