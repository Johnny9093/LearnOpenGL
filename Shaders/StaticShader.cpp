#include "StaticShader.h"
#include "MatrixMath.h"

const char *StaticShader::VERTEX_FILE = "shaders\\static.vrt.s";
const char *StaticShader::FRAGMENT_FILE = "shaders\\static.frg.s";

StaticShader::StaticShader() {
	ShaderProgram::initialize(VERTEX_FILE, FRAGMENT_FILE);
}

void StaticShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
	ShaderProgram::bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations() {
	transMat_location = ShaderProgram::getUniformLocation("transformationMatrix");
	projMat_location = ShaderProgram::getUniformLocation("projectionMatrix");
	viewMat_location = ShaderProgram::getUniformLocation("viewMatrix");
	lightPosition_location = ShaderProgram::getUniformLocation("lightPosition");
	lightColor_location = ShaderProgram::getUniformLocation("lightColor");
	shineDamper_location = ShaderProgram::getUniformLocation("shineDamper");
	reflectivity_location = ShaderProgram::getUniformLocation("reflectivity");
	ambientStrength_location = ShaderProgram::getUniformLocation("ambientStrength");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	ShaderProgram::setMat4(transMat_location, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
	ShaderProgram::setMat4(projMat_location, matrix);
}

void StaticShader::loadViewMatrix(Camera camera) {
	ShaderProgram::setMat4(viewMat_location, MatrixMath::createViewMatrix(camera));
}

void StaticShader::loadLight(Light light) {
	ShaderProgram::setVec3(lightPosition_location, light.getPosition());
	ShaderProgram::setVec3(lightColor_location, light.getColor());
}

void StaticShader::loadSpecularLighting(float damper, float reflectivity) {
	ShaderProgram::setFloat(shineDamper_location, damper);
	ShaderProgram::setFloat(reflectivity_location, reflectivity);
}

void StaticShader::loadAmbientLighting(float ambientStrength) {
	ShaderProgram::setFloat(ambientStrength_location, ambientStrength);
}
