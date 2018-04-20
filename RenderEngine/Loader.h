#pragma once

#include "RawModel.h"
#include <vector>

class Loader
{
public:
	RawModel loadToVAO(std::vector<float> vertices, std::vector<unsigned int> indices);
	void cleanUp();

private:
	std::vector<unsigned int> vaoIds;
	std::vector<unsigned int> vboIds;

	int createVAO();
	void storeDataInAttributeList(int attributeNumber, std::vector<float> vertices);
	void bindIndicesBuffer(std::vector<unsigned int> indices);
	void unbindVAO();
};

