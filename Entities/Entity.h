#pragma once

#include "TexturedModel.h"
#include <glm\glm.hpp>

class Entity {
public:
	Entity(TexturedModel model, glm::vec3 position, float rx, float ry, float rz, glm::vec3 scale);
	Entity(TexturedModel model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);

	void move(float dx, float dy, float dz);
	void rotate(float rx, float ry, float rz);
	void scale(float sx, float sy, float sz);

	TexturedModel getModel() const;
	glm::vec3 getPosition();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	glm::vec3 getScale();

	void setModel(TexturedModel model);
	void setPosition(glm::vec3 position);
	void setRotationX(float rotationX);
	void setRotationY(float rotationY);
	void setRotationZ(float rotationZ);
	void setScale(glm::vec3 scale);

private:
	TexturedModel model;
	glm::vec3 v_position;
	float rotationX;
	float rotationY;
	float rotationZ;
	glm::vec3 v_scale;
};