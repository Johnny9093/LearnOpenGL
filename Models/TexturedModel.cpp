#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel rawModel, const Texture modelTexture): 
	model(rawModel),
	texture(modelTexture) { }

RawModel TexturedModel::getRawModel() {
	return model;
}

Texture TexturedModel::getTexture() {
	return texture;
}
