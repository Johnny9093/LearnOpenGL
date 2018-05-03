#pragma once

#include <functional>
#include "RawModel.h"
#include "Texture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel model, const Texture texture);

	RawModel getRawModel() const;
	Texture getTexture() const;

private:
	RawModel model;
	Texture texture;
};

struct TexturedModelHasher
{
	size_t
	operator()(const TexturedModel & obj) const {
		unsigned int id = obj.getTexture().getTextureId();
		return std::hash<unsigned int>()(id);
	}
};

struct TexturedModelComparator
{
	bool
	operator()(const TexturedModel & obj1, const TexturedModel & obj2) const {
		return obj1.getTexture().getTextureId() == obj2.getTexture().getTextureId();
	}
};