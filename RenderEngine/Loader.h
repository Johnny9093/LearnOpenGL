#pragma once

#include "RawModel.h"
#include <vector>

class Loader
{
public:
	RawModel loadToVAO(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
	unsigned int loadTexture(const char *texturePath);
	void cleanUp();

private:
	std::vector<unsigned int> vaoIds;
	std::vector<unsigned int> vboIds;
	std::vector<unsigned int> textureIds;

	unsigned int createVAO();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> vertices);
	void bindIndicesBuffer(std::vector<unsigned int> indices);
	void unbindVAO();
};

