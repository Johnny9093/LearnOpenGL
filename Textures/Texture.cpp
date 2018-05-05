#include "Texture.h"

Texture::Texture(unsigned int id) {
	textureId = id;
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
