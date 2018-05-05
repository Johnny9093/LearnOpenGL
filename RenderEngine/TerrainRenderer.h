#pragma once

#include "TerrainShader.h"
#include "Terrain.h"
#include <glm/glm.hpp>

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader *shader);

	void render(const std::vector<const Terrain*> terrains) const;

	void TerrainRenderer::prepareTerrain(const Terrain *terrain) const;
	void TerrainRenderer::unbindTerrain() const;
	void TerrainRenderer::loadModelMatrix(const Terrain *terrain) const;

private:
	TerrainShader *shader;
};