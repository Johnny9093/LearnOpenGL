#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::move(glm::vec3 delta) {
	Camera::move(delta.x, delta.y, delta.z);
}

void Camera::move(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Camera::rotate(glm::vec3 angle) {
	Camera::rotate(angle.x, angle.y, angle.z);
}
void Camera::rotate(float ax, float ay, float az) {
	front.x += ax;
	front.y += ay;
	front.z += az;
}

void Camera::setPosition(glm::vec3 position) {
	Camera::setPosition(position.x, position.y, position.z);
}

void Camera::setPosition(float px, float py, float pz) {
	position.x = px;
	position.y = py;
	position.z = pz;
}

void Camera::setFront(glm::vec3 angle) {
	Camera::setFront(angle.x, angle.y, angle.z);
}

void Camera::setFront(float ax, float ay, float az) {
	front.x = ax;
	front.y = ay;
	front.z = az;
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getFront() {
	return front;
}

glm::vec3 Camera::getUp() {
	return up;
}