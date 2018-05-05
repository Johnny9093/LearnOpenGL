#include "TerrainShader.h"
#include "MatrixMath.h"

const char *TerrainShader::VERTEX_FILE = "shaders\\terrain.vertex.s";
const char *TerrainShader::FRAGMENT_FILE = "shaders\\terrain.fragment.s";

TerrainShader::TerrainShader() {
	ShaderProgram::initialize(VERTEX_FILE, FRAGMENT_FILE);
}

void TerrainShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
	ShaderProgram::bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() {
	transMat_location = ShaderProgram::getUniformLocation("transformationMatrix");
	projMat_location = ShaderProgram::getUniformLocation("projectionMatrix");
	viewMat_location = ShaderProgram::getUniformLocation("viewMatrix");
	lightPosition_location = ShaderProgram::getUniformLocation("lightPosition");
	lightColor_location = ShaderProgram::getUniformLocation("lightColor");
	shineDamper_location = ShaderProgram::getUniformLocation("shineDamper");
	reflectivity_location = ShaderProgram::getUniformLocation("reflectivity");
	ambientStrength_location = ShaderProgram::getUniformLocation("ambientStrength");
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) const {
	ShaderProgram::setMat4(transMat_location, matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 matrix) const {
	ShaderProgram::setMat4(projMat_location, matrix);
}

void TerrainShader::loadViewMatrix(const Camera *camera) const {
	ShaderProgram::setMat4(viewMat_location, MatrixMath::createViewMatrix(camera));
}

void TerrainShader::loadLight(const Light *light) const {
	ShaderProgram::setVec3(lightPosition_location, light->getPosition());
	ShaderProgram::setVec3(lightColor_location, light->getColor());
}

void TerrainShader::loadSpecularLighting(float damper, float reflectivity) {
	ShaderProgram::setFloat(shineDamper_location, damper);
	ShaderProgram::setFloat(reflectivity_location, reflectivity);
}

void TerrainShader::loadAmbientLighting(float ambientStrength) {
	ShaderProgram::setFloat(ambientStrength_location, ambientStrength);
}
