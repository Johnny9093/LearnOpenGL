#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out vec2 texCoord;

uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * vec4(position, 1.0);
	texCoord = textureCoords;
}