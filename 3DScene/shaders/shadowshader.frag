#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float calcShadow(vec4 FragPos,vec3 lightDir,vec3 normal);


void main ()
{
	vec3 color= texture(diffuseTexture,fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(0.5);


	vec3 ambient=0.3*color;

	//Diff
	vec3 lightdir =normalize(lightPos-fs_in.FragPos);
	float diff= max(dot(lightdir,normal),0.0);
    vec3 diffuse= lightColor*diff;
	
	//spec
    vec3 viewDir = normalize(viewPos-fs_in.FragPos);
    vec3 halfwayDir = normalize(lightdir+viewDir);
    float spec =pow(max(dot(halfwayDir,normal),0.0),32.0);
    vec3 specular = spec*lightColor;

    float shadow = calcShadow(fs_in.FragPosLightSpace,lightdir,normal);
    vec3 lighting = (ambient +(1.0-shadow) * (diffuse + specular))*color;

    FragColor=vec4(lighting,1.0f);
}


float calcShadow(vec4 fragpos,vec3 lightDir,vec3 normal)
{
 vec3 projpos = fragpos.xyz/fragpos.w;
//from [-1,1] (ndc) to [0,1]
projpos = projpos*0.5 + 0.5;	

if(projpos.z>1.0)
{
	return 0.0;
}

float closestDepth = texture(shadowMap,projpos.xy).r;

float currentDepth = projpos.z;

float bias= max(0.05*(1.0-dot(normal,lightDir)),0.005);
//float shadow = currentDepth -bias> closestDepth? 1.0 : 0.0;
 
float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projpos.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

return shadow;
}