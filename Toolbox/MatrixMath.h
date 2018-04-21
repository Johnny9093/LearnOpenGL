#pragma once

#include "Camera.h"

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

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	static glm::mat4 createViewMatrix(Camera camera) {
		return glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
	}

	//static glm::mat4 createViewMatrix(Camera camera) {
	//	glm::mat4 viewMatrix = glm::mat4();

	//	/*viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getDirection().x), glm::vec3(1, 0, 0));
	//	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getDirection().y), glm::vec3(0, 1, 0));
	//	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getDirection().z), glm::vec3(0, 0, 1));

	//	glm::vec3 negativePosition = -camera.getPosition();
	//	viewMatrix = glm::translate(viewMatrix, negativePosition);*/

	//	viewMatrix = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getFront(), camera.getUp());

	//	return viewMatrix;
	//}

	static glm::mat4 createProjectionMatrix(Camera camera, float aspectRatio, float nearPlane, float farPlane) {
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), aspectRatio, nearPlane, farPlane);
		return projectionMatrix;
	}
};