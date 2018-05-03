#pragma once

#include <unordered_map>
#include "Renderer.h"
#include "StaticShader.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"

class MasterRenderer
{
public:
	MasterRenderer();

	void render(Light sun, Camera camera);
	void addEntity(Entity entity);
	void cleanUp();

private:
	Renderer renderer;
	StaticShader shader;

	std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities;
};

