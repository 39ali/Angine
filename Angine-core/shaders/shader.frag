#version 330 core

layout(location = 0)out vec4 color;

in  vec3 out_color;
in vec2 textCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main ()
{
	
color = mix (texture(tex0,textCoord),texture(tex1,textCoord),0.2)  ;// * vec4(out_color.xyz, 1.0f);

}