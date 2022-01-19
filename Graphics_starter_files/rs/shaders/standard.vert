#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	FragPos = vec3(model * vec4(aPosition, 1.0f));
	Normal = transpose(inverse(mat3(model))) * aNormal;
	gl_Position = proj * view * model * vec4(aPosition, 1.0f);
}