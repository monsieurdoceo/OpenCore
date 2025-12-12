#version 330 core
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
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

vec3 calculateLightDirection(DirLight dirLight, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{ 
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = calculateLightDirection(dirLight, norm, viewDir);
    for (int i = 0; i < NR_POINT_LIGHTS; i++) result += calculatePointLight(pointLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 calculateLightDirection(DirLight dirLight, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = dirLight.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = dirLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = dirLight.specular * spec * texture(material.specular, TexCoords).rgb;

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 ambient = pointLight.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = pointLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = pointLight.specular * spec * texture(material.specular, TexCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

