#include "Camera.h"

void Camera::move(glm::vec3 delta) {
	Camera::move(delta.x, delta.y, delta.z);
}

void Camera::move(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

glm::vec3 Camera::getPosition() {
	return position;
}

float Camera::getPitch() {
	return pitch;
}

float Camera::getYaw() {
	return yaw;
}

float Camera::getRoll() {
	return roll;
}