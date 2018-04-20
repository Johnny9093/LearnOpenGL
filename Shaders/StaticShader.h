#pragma once

#include "ShaderProgram.h"
#include <glm\glm.hpp>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	void loadTransformationMatrix(glm::mat4 matrix);

	static const char *VERTEX_FILE;
	static const char *FRAGMENT_FILE;

	unsigned int transMat_location;
	unsigned int projMat_location;
};