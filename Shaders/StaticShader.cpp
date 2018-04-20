#include "StaticShader.h"

const char *StaticShader::VERTEX_FILE = "shaders\\static.vs";
const char *StaticShader::FRAGMENT_FILE = "shaders\\static.fs";

StaticShader::StaticShader() {
	ShaderProgram::initialize(VERTEX_FILE, FRAGMENT_FILE);
}

void StaticShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
}