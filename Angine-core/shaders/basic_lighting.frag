#version 330 core 

out vec4 color;

in vec3 fragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
sampler2D diffuse;
sampler2D specular;
float shininess;
};


struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	

	vec3 ambient ;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};


struct SpotLight 
{
vec3 position;
vec3 direction;

vec3 ambient;
vec3 diffuse; 
vec3 specular;

float cutOff;
float outerCutOff;

float constant ; 
float linear;
float quadratic;
};

#define NUM_POINT_LIGHTS 4

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light , vec3 normal , vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 viewDir,vec3 fragPos);
vec3 CalcSpotLight(SpotLight light , vec3 normal , vec3 viewDir , vec3 fragPos);

void main ()
{

vec3 normal = normalize(Normal);
vec3 viewDir =normalize(viewPos-fragPos); 

vec3 result = CalcDirLight(dirLight , normal , viewDir);

for (int i =0 ; i <NUM_POINT_LIGHTS ;i++)
{
	
	result+= CalcPointLight(pointLights[i],normal,viewDir,fragPos);
}

result += CalcSpotLight(spotLight,normal,viewDir,fragPos);

color = vec4 (result,1.0f);
}


vec3 CalcDirLight(DirLight light , vec3 normal , vec3 viewDir)
{
	
  vec3 lightDir = normalize(-light.direction);
   // diffuse
  float diff = max(dot(normal , lightDir),0.0);
   
   // specular 
  vec3 reflectedDir = reflect(-lightDir,normal);
  float spec = pow(max(dot(viewDir, reflectedDir),0.0),material.shininess);

  //
  vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
  vec3 diffuse = light.diffuse *diff* vec3 (texture(material.diffuse, TexCoords));
  vec3 specular = light.specular *spec* vec3 (texture (material.specular, TexCoords));

  return ambient+diffuse+specular;
};


vec3 CalcPointLight(PointLight light , vec3 normal  , vec3 viewDir , vec3 fragPos)
{
	vec3 lightDir = normalize (light.position-fragPos);

    // diffuse 
   
    float diff= max(dot(lightDir,normal),0.0);

    // specular 

    vec3 reflectedDir = reflect(-lightDir,normal);

    float spec = pow(max(dot(reflectedDir , viewDir),0.0f),material.shininess);
    
    //pointLight calc

    float distance = length(light.position-fragPos);
    float intensity = 1.0f/(light.constant + light.linear*distance + light.quadratic*(distance* distance));


    //results 

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse *diff* vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular*spec * vec3(texture(material.specular,TexCoords));
    return (ambient + diffuse + specular)*intensity;
};

vec3 CalcSpotLight(SpotLight light , vec3 normal , vec3 viewDir , vec3 fragPos)
{
vec3 lightDir= normalize(light.position-fragPos);
	

// diffuse 
float diff = max(dot(lightDir,normal),0.0f);

// specular 
vec3 reflectDir =reflect(-lightDir,normal);
float spec = pow(max(dot(reflectDir, viewDir),0.0f),material.shininess);


//attenuation

float distance = length(fragPos- light.position);
float attenuation= 1.0f / (light.constant + light.linear*distance + light.quadratic*(distance*distance));



/// spot light cal
float theta= dot (lightDir,normalize(-light.direction));
float epsilon = light.cutOff - light.outerCutOff;
float intensity =clamp((theta - light.outerCutOff)/epsilon,0.0f,1.0f);

vec3 ambient = light.ambient * diff * vec3(texture(material.diffuse,TexCoords));
vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

return (ambient + diffuse + specular)*attenuation*intensity;
};