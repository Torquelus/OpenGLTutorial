#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inCol;

out vec4 vertexCol;

void main(){
	gl_Position = vec4(inPos, 1.0f);
	vertexCol = inCol;
}