#include "StaticShader.h"

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
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	ShaderProgram::setMat4(transMat_location, matrix);
}