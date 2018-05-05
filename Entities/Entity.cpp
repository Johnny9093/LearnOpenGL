#include "Entity.h"

Entity::Entity(const TexturedModel model, const glm::vec3 position, const float rx, const float ry, const float rz, const glm::vec3 scale):
	model(model) {
	Entity::v_position = position;
	rotationX = rx;
	rotationY = ry;
	rotationZ = rz;
	Entity::v_scale = scale;
}

Entity::Entity(const TexturedModel model, const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy, const float sz):
	model(model) {
	Entity::v_position = glm::vec3(px, py, pz);
	rotationX = rx;
	rotationY = ry;
	rotationZ = rz;
	Entity::v_scale = glm::vec3(sx, sy, sz);
}

void Entity::move(const float dx, const float dy, const float dz) {
	v_position.x += dx;
	v_position.y += dy;
	v_position.z += dz;
}

void Entity::rotate(const float rx, const float ry, const float rz) {
	rotationX += rx;
	rotationY += ry;
	rotationZ += rz;
}

void Entity::scale(const float sx, const float sy, const float sz) {
	v_scale.x *= sx;
	v_scale.y *= sy;
	v_scale.z *= sz;
}

TexturedModel Entity::getModel() const {
	return model;
}

glm::vec3 Entity::getPosition() const {
	return v_position;
}

float Entity::getRotationX() const {
	return rotationX;
}

float Entity::getRotationY() const {
	return rotationY;
}

float Entity::getRotationZ() const {
	return rotationZ;
}

glm::vec3 Entity::getScale() const {
	return v_scale;
}

void Entity::setModel(const TexturedModel model) {
	Entity::model = model;
}

void Entity::setPosition(const glm::vec3 position) {
	Entity::v_position = position;
}

void Entity::setRotationX(const float rotationX) {
	Entity::rotationX = rotationX;
}

void Entity::setRotationY(const float rotationY) {
	Entity::rotationY = rotationY;
}

void Entity::setRotationZ(const float rotationZ) {
	Entity::rotationZ = rotationZ;
}

void Entity::setScale(const glm::vec3 scale) {
	Entity::v_scale = scale;
}
