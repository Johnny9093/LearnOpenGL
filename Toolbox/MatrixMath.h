#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class MatrixMath
{
public:
	static glm::mat4 createTransformationMatrix(const glm::vec3 translation, const float rx, const float ry, const float rz, const glm::vec3 scale) {
		// Create identity matrix
		glm::mat4 transformation;
		transformation = glm::translate(transformation, translation);
		transformation = glm::rotate(transformation, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		transformation = glm::rotate(transformation, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		transformation = glm::rotate(transformation, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		transformation = glm::scale(transformation, scale);
		return transformation;
	};
};

