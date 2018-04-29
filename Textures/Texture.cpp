#include "Texture.h"

Texture::Texture(unsigned int id) {
	textureId = id;
}

unsigned int Texture::getTextureId() {
	return textureId;
}

float Texture::getShineDamper() {
	return shineDamper;
}

void Texture::setShineDamper(float shineDamper) {
	Texture::shineDamper = shineDamper;
}

float Texture::getReflectivity() {
	return reflectivity;
}

void Texture::setReflectivity(float reflectivity) {
	Texture::reflectivity = reflectivity;
}
