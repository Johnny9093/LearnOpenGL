#pragma once

class Texture
{
public:
	Texture(unsigned int id);

	unsigned int getTextureId();
private:
	unsigned int textureId;
};

