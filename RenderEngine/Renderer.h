#pragma once

#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"

class Renderer
{
public:
	void prepare(StaticShader shader, Camera camera);
	void render(Entity entity, StaticShader shader);

private:
	static const float NEAR_PLANE;
	static const float FAR_PLANE;

	glm::mat4 projectionMatrix;
};