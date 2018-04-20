#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel model, const ModelTexture texture);

	RawModel getModel();
	ModelTexture getTexture();

private:
	RawModel model;
	ModelTexture texture;
};