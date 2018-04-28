#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
	Light::position = position;
	Light::color = color;
}

glm::vec3 Light::getPosition() {
	return position;
}

glm::vec3 Light::getColor()
{
	return color;
}

void Light::setPosition(glm::vec3 position) {
	Light::position = position;
}

void Light::setColor(glm::vec3 color) {
	Light::color = color;
}