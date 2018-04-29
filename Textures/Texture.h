#pragma once

class Texture
{
public:
	Texture(unsigned int id);

	unsigned int getTextureId();

	float getShineDamper();
	void setShineDamper(float shineDamper);

	float getReflectivity();
	void setReflectivity(float reflectivity);

private:
	unsigned int textureId;

	float shineDamper;
	float reflectivity;
};

