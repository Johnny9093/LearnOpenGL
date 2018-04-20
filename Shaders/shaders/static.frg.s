#version 330 core

in vec2 texCoord;
out vec4 color;
uniform sampler2D aTexture;

void main()
{
   // FragColor = gradient;
   // FragColor = texture(texture1, texCoord) * vec4(color, 1.0); // colored texture
   // FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(-texCoord.x, texCoord.y)), mixValue); // mixed textures
   // FragColor = vec4(color, 1.0);
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

   color = texture(aTexture, texCoord);
}