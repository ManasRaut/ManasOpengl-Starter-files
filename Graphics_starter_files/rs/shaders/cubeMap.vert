#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 view;
uniform mat4 proj;

out vec3 iTexCoords;

void main() {
	iTexCoords = aPosition;
	vec4 pos = proj * view * vec4(aPosition, 1.0f);
	gl_Position = pos.xyww;
}