#include "Texture.h"

Texture::Texture(unsigned int id) {
	textureId = id;
	shineDamper = 0;
	reflectivity = 0;
	hasTransparency = false;
	useFakeLighting = false;
}

unsigned int Texture::getTextureId() const {
	return textureId;
}

const float Texture::getShineDamper() const {
	return shineDamper;
}

const void Texture::setShineDamper(const float shineDamper) {
	Texture::shineDamper = shineDamper;
}

const float Texture::getReflectivity() const {
	return reflectivity;
}

const void Texture::setReflectivity(const float reflectivity) {
	Texture::reflectivity = reflectivity;
}

const void Texture::setHasTransparency(const bool hasTransparency) {
	Texture::hasTransparency = hasTransparency;
}

const bool Texture::getHasTransparency() const {
	return Texture::hasTransparency;
}

const void Texture::setUseFakeLighting(const bool useFakeLighting) {
	Texture::useFakeLighting = useFakeLighting;
}

const bool Texture::getUseFakeLighting() const {
	return Texture::useFakeLighting;
}