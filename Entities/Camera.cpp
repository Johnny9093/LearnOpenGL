//#include "Camera.h"
//
//Camera::Camera() {
//	position = glm::vec3(0.0f, 0.0f, 3.0f);
//	front = glm::vec3(0.0f, 0.0f, -1.0f);
//	up = glm::vec3(0.0f, 1.0f, 0.0f);
//}
//
//void Camera::move(glm::vec3 delta) {
//	Camera::move(delta.x, delta.y, delta.z);
//}
//
//void Camera::move(float dx, float dy, float dz) {
//	position.x += dx;
//	position.y += dy;
//	position.z += dz;
//}
//
//void Camera::setPosition(glm::vec3 position) {
//	Camera::position = position;
//}
//
//void Camera::setPosition(float px, float py, float pz) {
//	position.x = px;
//	position.y = py;
//	position.z = pz;
//}
//
//void Camera::setFront(glm::vec3 direction) {
//	front = direction;
//}
//
//void Camera::setFront(float dx, float dy, float dz) {
//	front.x = dx;
//	front.y = dy;
//	front.z = dz;
//}
//
//glm::vec3 Camera::getPosition() {
//	return position;
//}
//
//glm::vec3 Camera::getFront() {
//	return front;
//}
//
//glm::vec3 Camera::getUp() {
//	return up;
//}