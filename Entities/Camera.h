#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	void move(glm::vec3 delta);
	void move(float dx, float dy, float dz);
	void givePitch(float pitch);
	void giveYaw(float yaw);
	void giveRoll(float roll);


	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();

private:
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;
};

