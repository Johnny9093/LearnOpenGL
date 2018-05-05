#include "Light.h"

Light::Light(const glm::vec3 position, const glm::vec3 color) {
	Light::position = position;
	Light::color = color;
}

glm::vec3 Light::getPosition() const {
	return position;
}

glm::vec3 Light::getColor() const {
	return color;
}

void Light::setPosition(glm::vec3 position) {
	Light::position = position;
}

void Light::setColor(glm::vec3 color) {
	Light::color = color;
}