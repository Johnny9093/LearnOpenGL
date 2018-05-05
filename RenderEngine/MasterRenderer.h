#pragma once

#include <unordered_map>
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "TerrainRenderer.h"
#include "TerrainShader.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"

class MasterRenderer
{
public:
	MasterRenderer(const Camera *camera);

	void render(const Light *sun, const Camera *camera);
	void addEntity(const Entity entity);
	void addTerrain(const Terrain *terrain);
	void cleanUp();

private:
	static const float NEAR_PLANE;
	static const float FAR_PLANE;

	EntityRenderer entityRenderer;
	StaticShader entityShader;

	TerrainRenderer terrainRenderer;
	TerrainShader terrainShader;

	std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities;
	std::vector<const Terrain*> terrains;

	glm::mat4 projectionMatrix;

	void prepare() const;
};