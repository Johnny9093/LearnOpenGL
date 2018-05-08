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

	const void setHasTransparency(const bool hasTransparency);
	const bool getHasTransparency() const;

	const void setUseFakeLighting(const bool useFakeLighting);
	const bool getUseFakeLighting() const;

private:
	unsigned int textureId;

	float shineDamper;
	float reflectivity;

	bool hasTransparency;
	bool useFakeLighting;
};

