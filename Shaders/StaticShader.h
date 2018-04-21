#pragma once

#include "ShaderProgram.h"
#include "Camera.h"

#include <glm\glm.hpp>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera camera);

protected:
	void bindAttributes();
	void getAllUniformLocations();

private:
	static const char *VERTEX_FILE;
	static const char *FRAGMENT_FILE;

	unsigned int transMat_location;
	unsigned int projMat_location;
	unsigned int viewMat_location;
};