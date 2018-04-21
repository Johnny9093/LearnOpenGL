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
}

void StaticShader::getAllUniformLocations() {
	transMat_location = ShaderProgram::getUniformLocation("transformationMatrix");
	projMat_location = ShaderProgram::getUniformLocation("projectionMatrix");
	viewMat_location = ShaderProgram::getUniformLocation("viewMatrix");
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