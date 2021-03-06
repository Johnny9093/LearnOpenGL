#version 330 core

in vec2 texCoord;
in vec3 surfaceNormal;
in vec3 toLight;
in vec3 toCamera;
in float visibility;

out vec4 color;

uniform sampler2D aTexture;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;
uniform float ambientStrength;
uniform vec3 skyColor;

void main()
{
	vec4 textureColor = texture(aTexture, texCoord);

	if (textureColor.a < 0.5) {
		discard;
	}

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitToLight = normalize(toLight);
	vec3 unitToCamera = normalize(toCamera);

	// ambient lighting
	vec3 ambient = ambientStrength * lightColor;

	// diffuse lighting
	float similarity = dot(unitNormal, unitToLight);
	float brightness = max(similarity, 0);
	vec3 diffuse = brightness * lightColor;

	// specular lighting
	vec3 lightDirection = -unitToLight;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	float specularFactor = dot(reflectedLightDirection, unitToCamera);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 specular = dampedFactor * reflectivity * lightColor;
	
	// color = vec4(1.0, 1.0, 1.0, 1.0);
	// color = texture(aTexture, texCoord);
	// color = texture(aTexture, texCoord) + vec4(specular, 1.0);
	// color = vec4(diffuse, 1.0) * texture(aTexture, texCoord) + vec4(specular, 1.0);
	color = vec4(ambient + diffuse, 1.0) * textureColor + vec4(specular, 1.0);
	color = mix(vec4(skyColor, 1.0), color, visibility);
}