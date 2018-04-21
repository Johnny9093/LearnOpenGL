#pragma once

#include "RawModel.h"
#include "Texture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel model, const Texture texture);

	RawModel getRawModel();
	Texture getTexture();

private:
	RawModel model;
	Texture texture;
};