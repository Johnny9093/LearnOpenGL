#pragma once

#include <unordered_map>
#include "Entity.h"
#include "TexturedModel.h"
#include "StaticShader.h"
#include "Camera.h"

class EntityRenderer
{
public:
	EntityRenderer::EntityRenderer(StaticShader *shader);

	void render(std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities) const;

private:
	StaticShader *shader;

	void prepareTexturedModel(const TexturedModel model) const;
	void unbindTexturedModel() const;
	void prepareInstance(const Entity entity) const;
};