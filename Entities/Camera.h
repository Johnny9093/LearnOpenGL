#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	Camera();

	void move(glm::vec3 delta);
	void move(float dx, float dy, float dz);

	void rotate(glm::vec3 angle);
	void rotate(float ax, float ay, float az);

	void setPosition(glm::vec3 position);
	void setPosition(float px, float py, float pz);

	void setFront(glm::vec3 angle);
	void setFront(float ax, float ay, float az);

	glm::vec3 getPosition();
	glm::vec3 getFront();
	glm::vec3 getUp();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
};