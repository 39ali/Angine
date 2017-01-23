#version 330 core 

layout(location=0) in vec3 pos ;
layout(location=1) in vec3 color;
layout(location=2) in vec2 in_textcoord;

out vec3 out_color;
out vec2 textCoord;

uniform mat4 mvp;

void main ()
{
	
gl_Position= mvp * vec4(pos.x , pos.y, pos.z , 1.0);

out_color = color;
textCoord= in_textcoord;

}