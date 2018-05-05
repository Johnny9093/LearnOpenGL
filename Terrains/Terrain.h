#pragma once

#include "Loader.h"
#include "Texture.h"
#include "RawModel.h"

class Terrain
{
public:
	Terrain(float gridX, float gridZ, Loader *loader, Texture &terrainTexture);

	float getX() const;
	float getZ() const;
	const RawModel &getModel() const;
	const Texture &getTexture() const;
private:
	static const short SIZE;
	static const short VERTEX_COUNT;

	float x;
	float z;
	RawModel model;
	Texture texture;

	static RawModel generateTerrain(Loader *loader);
};