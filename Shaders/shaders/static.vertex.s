#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 surfaceNormal;
out vec3 toLight;
out vec3 toCamera;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform int useFakeLighting;

const float density = 0.03;
const float gradient = 1.5;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	vec4 positionRelativeToCam = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCam;
	texCoord = textureCoords;

	vec3 actualNormal = normal;

	if (useFakeLighting > 0.5) {
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz;
	toLight = lightPosition - worldPosition.xyz;
	vec3 cameraPos = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	toCamera = cameraPos - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visibility = clamp(exp(-pow((distance * density), gradient)), 0.0, 1.0);
}