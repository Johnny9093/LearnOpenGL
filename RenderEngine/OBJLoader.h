#pragma once

#include "RawModel.h"
#include "Loader.h"

#include <glm\glm.hpp>

class OBJLoader
{
public:
	static RawModel loadObjModel(const std::string filePath, const Loader loader);

private:

	static void processVertex(unsigned int vin, unsigned int tin, unsigned int nin, std::vector<unsigned int> *indices,
							  std::vector<glm::vec2> *textures, std::vector<float> *texturesf,
							  std::vector<glm::vec3> *normals, std::vector<float> *normalsf);
};

