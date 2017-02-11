#version 330 core 

layout (location = 0 ) out vec4 color ;
in vec3 normal_out;
 in vec3 fragpos;


uniform vec3 modelcolor;
uniform vec3 lightcolor;
uniform vec3 lightposition;
uniform vec3 cameraposition;


float ambient=0.1;
float specularstrength=0.5;
void main ()
{

vec3 normal = normalize(normal_out);

vec3 lightDir=normalize(lightposition-fragpos);
float diffuse = max(dot(lightDir,normal),0.0);

vec3 reflectvec= reflect(-lightDir,normal); 
vec3 viewDir= normalize(cameraposition-fragpos);
float specular = pow(max(dot(viewDir,reflectvec),0.0),32) *specularstrength;



color = vec4(modelcolor*lightcolor*(ambient+diffuse + specular),1.0) ;

}

