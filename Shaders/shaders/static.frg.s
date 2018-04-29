#version 330 core

in vec2 texCoord;
in vec3 surfaceNormal;
in vec3 toLight;
in vec3 toCamera;

out vec4 color;

uniform sampler2D aTexture;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

void main()
{
   vec3 unitNormal = normalize(surfaceNormal);
   vec3 unitToLight = normalize(toLight);

   float dotProduct = dot(unitNormal, unitToLight);
   float brightness = max(dotProduct, 0.2);
   vec3 diffuse = brightness * lightColor;

   vec3 unitToCamera = normalize(toCamera);
   vec3 lightDirection = -unitToLight;
   vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

   float specularFactor = dot(reflectedLightDirection, unitToCamera);
   specularFactor = max(specularFactor, 0.0);

   float dampedFactor = pow(specularFactor, shineDamper);
   vec3 specularLighting = dampedFactor * reflectivity * lightColor;

   color = vec4(diffuse, 1.0) * texture(aTexture, texCoord) + vec4(specularLighting, 1.0);
}