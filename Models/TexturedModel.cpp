#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel rawModel, const Texture modelTexture): 
	model(rawModel),
	texture(modelTexture) { }

RawModel TexturedModel::getRawModel() const {
	return model;
}

Texture TexturedModel::getTexture() const {
	return texture;
}
