#include "Terrain.h"

#include <vector>

const short Terrain::SIZE = 100;
const short Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(float gridX, float gridZ, Loader *loader, Texture &terrainTexture): texture(terrainTexture), model(Terrain::generateTerrain(loader)) {
	x = gridX * SIZE;
	z = gridZ * SIZE;
}

float Terrain::getX() const {
	return x;
}

float Terrain::getZ() const {
	return z;
}

const RawModel &Terrain::getModel() const {
	return model;
}

const Texture &Terrain::getTexture() const {
	return texture;
}

RawModel Terrain::generateTerrain(Loader *loader) {
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices = std::vector<float>(count * 3);
	std::vector<float> normals = std::vector<float>(count * 3);
	std::vector<float> textureCoords = std::vector<float>(count * 2);
	std::vector<unsigned int> indices = std::vector<unsigned int>(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));

	int vertexPointer = 0;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	return loader->loadToVAO(vertices, textureCoords, normals, indices);
}

