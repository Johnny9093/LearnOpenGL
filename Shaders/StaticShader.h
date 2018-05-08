#pragma once

#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

#include <glm\glm.hpp>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void loadTransformationMatrix(glm::mat4 matrix) const;
	void loadProjectionMatrix(glm::mat4 matrix) const;
	void loadViewMatrix(const Camera *camera) const;
	void loadLight(const Light *light) const;
	void loadSpecularLighting(float damper, float reflectivity);
	void loadAmbientLighting(float ambientStrength);
	void loadUseFakeLighting(bool useFakeLighting);
	void loadSkyColor(glm::vec3 skyColor);

protected:
	void bindAttributes();
	void getAllUniformLocations();

private:
	static const char *VERTEX_FILE;
	static const char *FRAGMENT_FILE;

	unsigned int transMat_location;
	unsigned int projMat_location;
	unsigned int viewMat_location;
	unsigned int lightPosition_location;
	unsigned int lightColor_location;
	unsigned int shineDamper_location;
	unsigned int reflectivity_location;
	unsigned int ambientStrength_location;
	unsigned int useFakeLighting_location;
	unsigned int skyColor_location;
};