#version 330 core

in vec2 texCoord;
in vec3 surfaceNormal;
in vec3 toLight;

out vec4 color;

uniform sampler2D aTexture;
uniform vec3 lightColor;

void main()
{
   // FragColor = gradient;
   // FragColor = texture(texture1, texCoord) * vec4(color, 1.0); // colored texture
   // FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(-texCoord.x, texCoord.y)), mixValue); // mixed textures
   // FragColor = vec4(color, 1.0);
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

   vec3 unitNormal = normalize(surfaceNormal);
   vec3 unitToLight = normalize(toLight);

   float dotProduct = dot(unitNormal, unitToLight);
   float brightness = max(dotProduct, 0.0);
   vec3 diffuse = brightness * lightColor;

   color = vec4(diffuse, 1.0) * texture(aTexture, texCoord);
}