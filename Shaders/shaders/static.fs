#version 330 core
out vec4 FragColor;

//in vec3 color;
//in vec2 texCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float mixValue;

// uniform vec4 gradient;

void main()
{
   // FragColor = gradient;
   // FragColor = texture(texture1, texCoord);
   // FragColor = texture(texture1, texCoord) * vec4(color, 1.0); // colored texture
   // FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(-texCoord.x, texCoord.y)), mixValue); // mixed textures
   // FragColor = vec4(color, 1.0);
   FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}