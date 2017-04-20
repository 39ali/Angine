#version 330 core 

layout(location=0) in vec4 pos;
uniform mat4 mvp ;

out VS_OUT
{
	vec2 uv;
    
} vs_out;


void  main()
{
gl_Position = mvp* vec4 (pos.xy,0.0,1.0f);
vs_out.uv = pos.zw;
}