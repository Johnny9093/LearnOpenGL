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

	static glm::mat4 createProjectionMatrix(float width, float height, float fieldOfView, float nearPlane, float farPlane) {
		glm::mat4 projectionMatrix = glm::perspectiveFov(fieldOfView, width, height, nearPlane, farPlane);

		/*float aspectRatio = (width / (float)height);
		float y_scale = (float)((1.0f / glm::tan(glm::radians(fieldOfView / 2.0f))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = farPlane - nearPlane;

		glm::mat4 projectionMatrix2 = glm::mat4(xB_scale, 0, 0, 0, 0, y_scale, 0, 0, 0, 0, -((farPlane + nearPlane) / frustum_length), -1, 0, 0, -((2 * nearPlane * farPlane) / frustum_length), 0);*/

		return projectionMatrix;
	}

	static glm::mat4 createViewMatrix(Camera camera) {
		glm::mat4 viewMatrix = glm::mat4();

		viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getRoll()), glm::vec3(0, 0, 1));
		glm::vec3 position = camera.getPosition();
		glm::vec3 negativePosition = -position;
		viewMatrix = glm::translate(viewMatrix, negativePosition);
		return viewMatrix;
	}
};