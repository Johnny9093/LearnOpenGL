#include "Entity.h"

Entity::Entity(TexturedModel model, glm::vec3 position, float rx, float ry, float rz, glm::vec3 scale):
	model(model) {
	Entity::v_position = position;
	rotationX = rx;
	rotationY = ry;
	rotationZ = rz;
	Entity::v_scale = scale;
}

Entity::Entity(TexturedModel model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz):
	model(model) {
	Entity::v_position = glm::vec3(px, py, pz);
	rotationX = rx;
	rotationY = ry;
	rotationZ = rz;
	Entity::v_scale = glm::vec3(sx, sy, sz);
}

void Entity::move(float dx, float dy, float dz) {
	v_position.x += dx;
	v_position.y += dy;
	v_position.z += dz;
}

void Entity::rotate(float rx, float ry, float rz) {
	rotationX += rx;
	rotationY += ry;
	rotationZ += rz;
}

void Entity::scale(float sx, float sy, float sz) {
	v_scale.x *= sx;
	v_scale.y *= sy;
	v_scale.z *= sz;
}

TexturedModel Entity::getModel() const {
	return model;
}

glm::vec3 Entity::getPosition() {
	return v_position;
}

float Entity::getRotationX() {
	return rotationX;
}

float Entity::getRotationY() {
	return rotationY;
}

float Entity::getRotationZ() {
	return rotationZ;
}

glm::vec3 Entity::getScale() {
	return v_scale;
}

void Entity::setModel(TexturedModel model) {
	Entity::model = model;
}

void Entity::setPosition(glm::vec3 position) {
	Entity::v_position = position;
}

void Entity::setRotationX(float rotationX) {
	Entity::rotationX = rotationX;
}

void Entity::setRotationY(float rotationY) {
	Entity::rotationY = rotationY;
}

void Entity::setRotationZ(float rotationZ) {
	Entity::rotationZ = rotationZ;
}

void Entity::setScale(glm::vec3 scale) {
	Entity::v_scale = scale;
}
