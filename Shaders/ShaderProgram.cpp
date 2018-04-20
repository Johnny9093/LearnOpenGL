#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

void ShaderProgram::initialize(const char *vertexFile, const char *fragmentFile) {
	vertexShaderId = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderId = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	bindAttributes();
	glLinkProgram(programId);
	glValidateProgram(programId);

	int success;
	char infoLog[512];

	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	// Linking error handling
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::start() {
	glUseProgram(programId);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::cleanUp() {
	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteProgram(programId);
}

void ShaderProgram::bindAttribute(int attribute, const char *variableName) {
	glBindAttribLocation(programId, attribute, variableName);
}

// Read and build the shader
int ShaderProgram::loadShader(const char *filePath, GLenum shaderType) {
	std::string codeString;
	std::ifstream fileStream;

	// exceptions (check)
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// read shader files
		fileStream.open(filePath);
		std::stringstream shaderStream;
		shaderStream << fileStream.rdbuf();
		fileStream.close();

		codeString = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char *code = codeString.c_str();

	unsigned int shaderId;
	int success;
	char infoLog[512];

	shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &code, NULL);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	// Compilation error handling
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::TYPE(" << shaderType << ")COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderId;
}

// Uniform utility functions

void ShaderProgram::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
}

void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
