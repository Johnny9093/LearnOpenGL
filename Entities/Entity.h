#pragma once

#include "TexturedModel.h"
#include <glm\glm.hpp>

class Entity {
public:
	Entity(const TexturedModel model, const glm::vec3 position, const float rx, const float ry, const float rz, const glm::vec3 scale);
	Entity(const TexturedModel model, const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy, const float sz);

	void move(const float dx, const float dy, const float dz);
	void rotate(const float rx, const float ry, const float rz);
	void scale(const float sx, const float sy, const float sz);

	TexturedModel getModel() const;
	glm::vec3 getPosition() const;
	float getRotationX() const;
	float getRotationY() const;
	float getRotationZ() const;
	glm::vec3 getScale() const;

	void setModel(const TexturedModel model);
	void setPosition(const glm::vec3 position);
	void setRotationX(const float rotationX);
	void setRotationY(const float rotationY);
	void setRotationZ(const float rotationZ);
	void setScale(const glm::vec3 scale);

private:
	TexturedModel model;
	glm::vec3 v_position;
	float rotationX;
	float rotationY;
	float rotationZ;
	glm::vec3 v_scale;
};