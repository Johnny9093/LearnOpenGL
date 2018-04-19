#pragma once

#include "RawModel.h"
#include <vector>

class Loader
{
public:
	RawModel loadToVAO(std::vector<float> data);
	void cleanUp();

private:
	std::vector<unsigned int> vaoIDs;
	std::vector<unsigned int> vboIDs;

	int createVAO();
	void storeDataInAttributeList(int attributeNumber, std::vector<float> data);
	void unbindVAO();
};

