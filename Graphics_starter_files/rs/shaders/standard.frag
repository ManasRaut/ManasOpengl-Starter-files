#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 cameraPos;

void main() {
	vec3 lightColor = vec3(1.0f);
	vec3 lightPos = vec3(-2.0f, 2.0f, -2.0f);
	vec3 matColor = vec3(0.6f);
	float specIntensity = 0.5f;
	float ambientIntensity = 0.6f;

	vec3 fNormal = normalize(Normal);

	vec3 ambient = ambientIntensity * lightColor;

	vec3 lightDirection = normalize(lightPos - FragPos);
	vec3 diffuse = lightColor * max(dot(lightDirection, fNormal), 0.0);

	vec3 viewDirection = normalize(cameraPos - FragPos);
	vec3 reflectVec = reflect(-lightDirection, fNormal);
	float spec = pow(max(dot(viewDirection, reflectVec), 0.0), 64);
	vec3 specular = spec * lightColor * specIntensity;

	vec3 FinalColor = (diffuse + ambient + specular) * matColor;;
	FragColor = vec4(FinalColor, 1.0f);
}