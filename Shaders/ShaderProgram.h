#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <string>

class ShaderProgram
{
public:
	void initialize(const char *vertexFile, const char *fragmentFile);
	void start();
	void stop();
	void cleanUp();
protected:
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;

	void bindAttribute(int attribute, const char *attributeName);
	int getUniformLocation(const char *uniformName);

	void setBool(const int uniformLocation, bool value) const;
	void setInt(const int uniformLocation, int value) const;
	void setFloat(const int uniformLocation, float value) const;
	void setVec2(const int uniformLocation, const glm::vec2 &value) const;
	void setVec2(const int uniformLocation, float x, float y) const;
	void setVec3(const int uniformLocation, const glm::vec3 &value) const;
	void setVec3(const int uniformLocation, float x, float y, float z) const;
	void setVec4(const int uniformLocation, const glm::vec4 &value) const;
	void setVec4(const int uniformLocation, float x, float y, float z, float w) const;
	void setMat2(const int uniformLocation, const glm::mat2 &mat) const;
	void setMat3(const int uniformLocation, const glm::mat3 &mat) const;
	void setMat4(const int uniformLocation, const glm::mat4 &mat) const;
	
private:
	int programId;
	int vertexShaderId;
	int fragmentShaderId;

	static int loadShader(const char *filePath, GLenum shaderType);
};

