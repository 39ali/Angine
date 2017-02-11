#version 330 core 

layout(location=0) in vec3 pos ;
layout(location=0) in vec3 normal;

out vec3 normal_out;
out vec3 fragpos ;

uniform mat4 mvp;
uniform mat4 modelmatrix;

void main ()
{
	
gl_Position= mvp*vec4(pos , 1.0);

fragpos= vec3 (modelmatrix* vec4(pos,1.0));

normal_out = mat3(transpose(inverse(modelmatrix))) * normal;  

}