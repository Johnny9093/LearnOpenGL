#pragma once

#include <unordered_map>
#include "Entity.h"
#include "TexturedModel.h"
#include "StaticShader.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer::Renderer(StaticShader *shader);

	void prepare(Camera camera);
	void render(std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities);

private:
	static const float NEAR_PLANE;
	static const float FAR_PLANE;

	glm::mat4 projectionMatrix;
	StaticShader *shader;

	void prepareTexturedModel(TexturedModel model);
	void unbindTexturedModel();
	void prepareInstance(Entity entity);
};