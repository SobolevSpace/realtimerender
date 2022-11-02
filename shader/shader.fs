#version 460 core
out vec4 FragColor;

in vec3 ourNorm;
in vec3 fragPos;
in vec2 ourCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

void main()
{
	float ambientStrength = 0.1f;
	//vec3 diffuse = (mix(texture(texture1, ourCoord), texture(texture2, ourCoord), 0.2) * vec4(lightColor, 1.0f)).xyz;
	
	vec3 ambient = ambientStrength * lightColor * material.ambient;

	vec3 lightDir = (lightPos - fragPos);
	float diffuseStrength = max(0.0f, dot(normalize(lightDir), ourNorm));
	vec3 diffuse = diffuseStrength * material.diffuse;

	vec3 viewDir = normalize(camPos - fragPos);
	vec3 perfectMirror = normalize(reflect(fragPos - lightPos, ourNorm));
	float specularStrength = 0.5;
	float spec = pow(max(0, dot(viewDir, perfectMirror)), material.shininess);
	vec3 specular = spec*specularStrength*lightColor*material.specular;

	FragColor = vec4(ambient + diffuse + specular, 1.0f);
}