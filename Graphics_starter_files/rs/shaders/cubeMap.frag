#version 330 core

in vec3 iTexCoords;

out vec4 FragColor;

uniform samplerCube cubeMap;

void main() {
	FragColor = texture(cubeMap, iTexCoords);
}