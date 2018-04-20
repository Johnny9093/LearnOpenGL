#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel rawModel, const ModelTexture modelTexture): 
	model(rawModel),
	texture(modelTexture) { }

RawModel TexturedModel::getModel() {
	return model;
}

ModelTexture TexturedModel::getTexture() {
	return texture;
}
