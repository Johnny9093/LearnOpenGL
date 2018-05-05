#pragma once

class Texture
{
public:
	Texture(unsigned int id);

	unsigned int getTextureId() const;

	const float getShineDamper() const;
	const void setShineDamper(const float shineDamper);

	const float getReflectivity() const;
	const void setReflectivity(const float reflectivity);

private:
	unsigned int textureId;

	float shineDamper;
	float reflectivity;
};

